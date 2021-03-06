#include <hardware/hardware.h>
#include <hardware/SampleOnTime.h>
#include <malloc.h>
#include <error.h>
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>

#include <stdio.h>
#include <stdlib.h>
#include "webrtc_aec.h"


#define ECHO_BUFFER_SIZE 160
#define TIME_DIFF 18


/**
 * @brief follows are user for debug, used to save wav files.
 */
#define DEBUG_RECORD
/**
 * @brief wave file head
 */
#ifdef DEBUG_RECORD
typedef struct{
	unsigned char riff[4];
	unsigned int file_length;
	unsigned char wav_flag[4];
	unsigned char fmt_flag[4];
	unsigned int transition;
	unsigned short format_tag;
	unsigned short channels;
	unsigned int sample_rate;
	unsigned int wave_rate;
	unsigned short block_align;
	unsigned short sample_bits;
	unsigned char data_flag[4];
	unsigned int data_length;
}wav_header;



/**
 * @brief to init a wave file head
 *
 * @param wave wav_header pointer
 * @param rate sample rate
 * @param bits sample per bits
 * @param channels sample channel numbers
 * @param size size of wave file
 */
static void init_wave_head(wav_header *wave,int rate,int bits,int channels, int size)
{
	memcpy(wave->riff,"RIFF",4);
	wave->file_length = 0;
	memcpy(wave->wav_flag,"WAVE",4);
	memcpy(wave->fmt_flag,"fmt ",4);
	wave->transition = 0x10;
	wave->format_tag = 0x01;
	wave->channels = channels;
	wave->sample_rate = rate;
	wave->wave_rate = rate*channels*bits/8;
	wave->block_align = channels*bits/8;
	wave->sample_bits = bits;
	memcpy(wave->data_flag,"data",4);
	wave->data_length = size;
}

/**
 * @brief write wave header into a wav file
 *
 * @param file_fd  file fd
 * @param wave wave header pointer
 */
static void set_wave_head(int file_fd, wav_header *wave)
{
	lseek(file_fd, 0, SEEK_SET);
	write(file_fd, wave, sizeof(wav_header));
}



/**
 * @brief get size of a file
 *
 * @param file_name name of the file you want to get
 *
 * @return size of the file
 */
static int get_file_size(char *file_name)
{
	struct stat statbuf;
	stat(file_name, &statbuf);
	int size = statbuf.st_size;
	return size;
}

/**
 * @brief write pcm data size into a wav file header
 *
 * @param filename the file name you want to write into
 * @param fd  file fd
 */
static void finally_set_wav_data_size(char *filename, int fd)
{
	int size = 0;
	wav_header wave;
	size = get_file_size(filename)-44;
	init_wave_head(&wave, 16000, 16, 1, size);
	set_wave_head(fd, &wave);

	printf("finish\n");

}


static void finally_set_wav_data_size_amic(char *filename, int fd)
{
	int size = 0;
	wav_header wave;
	size = get_file_size(filename)-44;
	init_wave_head(&wave, 8000, 16, 2, size);
	set_wave_head(fd, &wave);

	printf("finish\n");

}


static void finally_set_wav_data_size_dmic(char *filename, int fd)
{
	int size = 0;
	wav_header wave;
	size = get_file_size(filename)-44;
	init_wave_head(&wave, 8000, 16, 2, size);
	set_wave_head(fd, &wave);

	printf("finish\n");

}

#endif

//***************************************************************************************************************


/**
 * @brief set codec route for playback loop
 */
static void set_codec_route()
{
	system("amixer cset numid=6,iface=MIXER,name='Mic Volume' 2");
	system("amixer cset numid=4,iface=MIXER,name='Digital Capture Volume' 30");
	system("amixer cset numid=19,iface=MIXER,name='ADC Mux' 0");
	system("amixer cset numid=14,iface=MIXER,name='ADC Mode Mux' 1");
	system("amixer cset numid=12,iface=MIXER,name='AIADC Mux L' 0");
	system("amixer cset numid=11,iface=MIXER,name='AIADC Mux R' 1");
	system("amixer cset numid=10,iface=MIXER,name='ADC MIXER Mux' 3");
	system("amixer cset numid=9,iface=MIXER,name='mixer Enable' 1");
}



struct Devices {
	struct sample_on_time_device_t *sample_on_time;
};
int main(int argc, char *argv[])
{
	int err;
	hw_module_t* module;
	hw_device_t* device;
	struct Devices *devices;

	devices = (struct Devices*)malloc(sizeof(struct Devices));
	err = hw_get_module(SAMPLE_ON_TIME_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
	printf("err=%d id=%s\n", err, SAMPLE_ON_TIME_HARDWARE_MODULE_ID);
	if (err != 0){
		return -1;
	}
	err = module->methods->open(module, "sample_on_time", &device);
	if (err != 0) {
		return -1;
	}
	devices->sample_on_time = (struct sample_on_time_device_t *)device;

#ifdef DEBUG_RECORD
	wav_header *wave;
	int fd = open("/tmp/test.wav", O_RDWR | O_CREAT | O_TRUNC);

	wave = malloc(sizeof(wav_header));
	init_wave_head(wave, 16000, 16, 1, 0); /* configuration overwrite in finally_set_wav_data_size() */
	set_wave_head(fd, wave);

	int fd_amic = open("/tmp/test_amic.wav", O_RDWR | O_CREAT | O_TRUNC);
	int fd_dmic = open("/tmp/test_dmic.wav", O_RDWR | O_CREAT | O_TRUNC);

	init_wave_head(wave, 8000, 16, 2, 0); /* configuration overwrite in finally_set_wav_data_size() */
	set_wave_head(fd_amic, wave);

	init_wave_head(wave, 8000, 16, 2, 0); /* configuration overwrite in finally_set_wav_data_size() */
	set_wave_head(fd_dmic, wave);

#endif

	char amic_buf[1024];
	char dmic_buf[1024];
	char buf[1024];
	int time = 0;
	int ret = 0;
	int total_bytes = 0;



	if(argc == 2){
		time = atoi(argv[1]);
	}else{
		time = 30;
	}
	total_bytes = 8000 * 2 * 2 * time;

	set_codec_route();

	ingenic_apm_init();

	int id_amic = devices->sample_on_time->new_device(devices->sample_on_time, "hw:0,0", 8000, SND_PCM_FORMAT_S16_LE, 2);
	int id_dmic = devices->sample_on_time->new_device(devices->sample_on_time, "hw:0,2", 8000, SND_PCM_FORMAT_S16_LE, 2);


	devices->sample_on_time->device_start(devices->sample_on_time, id_amic);
	devices->sample_on_time->device_start(devices->sample_on_time, id_dmic);

	while(total_bytes > 0){
		ret = devices->sample_on_time->device_block_read(devices->sample_on_time, id_amic, amic_buf, ECHO_BUFFER_SIZE);
		ret = devices->sample_on_time->device_block_read(devices->sample_on_time, id_dmic, dmic_buf, ECHO_BUFFER_SIZE);
		total_bytes -= ret;

		ingenic_apm_set_far_frame((short *)amic_buf);
		ingenic_apm_set_near_frame((short *)dmic_buf, (short *)buf, TIME_DIFF);
#ifdef DEBUG_RECORD
		write(fd, buf, ECHO_BUFFER_SIZE);
		write(fd_amic, amic_buf, ECHO_BUFFER_SIZE);
		write(fd_dmic, dmic_buf, ECHO_BUFFER_SIZE);
#endif
	}

	devices->sample_on_time->device_stop(devices->sample_on_time, id_amic);
	devices->sample_on_time->device_stop(devices->sample_on_time, id_dmic);

#ifdef DEBUG_RECORD
	finally_set_wav_data_size("/tmp/test.wav",fd);
	finally_set_wav_data_size_amic("/tmp/test_amic.wav",fd_amic);
	finally_set_wav_data_size_dmic("/tmp/test_dmic.wav",fd_dmic);
#endif
	devices->sample_on_time->del_device(devices->sample_on_time, id_amic);
	devices->sample_on_time->del_device(devices->sample_on_time, id_dmic);

	devices->sample_on_time->common.close(device);

	return 0;



}
