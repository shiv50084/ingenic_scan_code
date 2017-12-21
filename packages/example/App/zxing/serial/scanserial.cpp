
#include "scanserial.h"





//#define dbprintf printf

/*******************************************************************
* 名称：                  UART0_Open
* 功能：                打开串口并返回串口设备文件描述
* 入口参数：        fd    :文件描述符     port :串口号(ttyS0,ttyS1,ttyS2)
* 出口参数：        正确返回为1，错误返回为0
*******************************************************************/
int UART0_Open(char* port)
{
  int fd;
  fd = open( port, O_RDWR | O_NOCTTY | O_NDELAY);
  if (FALSE == fd)
  {
    dbprintf("Can't Open Serial Port\r\n");
    return (FALSE);
  }
  //恢复串口为阻塞状态
  if (fcntl(fd, F_SETFL, 0) < 0)
  {
    dbprintf("fcntl failed!\n");
    return (FALSE);
  }
  else
  {
    dbprintf("fcntl=%d\n", fcntl(fd, F_SETFL, 0));
  }
  //测试是否为终端设备
  if (0 == isatty(STDIN_FILENO))
  {
    dbprintf("standard input is not a terminal device\n");
    return (FALSE);
  }
  else
  {
    dbprintf("isatty success!\n");
  }
    dbprintf("fd->open=%d\n", fd);
  return fd;
}
/*******************************************************************
* 名称：                UART0_Close
* 功能：                关闭串口并返回串口设备文件描述
* 入口参数：        fd    :文件描述符     port :串口号(ttyS0,ttyS1,ttyS2)
* 出口参数：        void
*******************************************************************/

void UART0_Close(int fd)
{
  close(fd);
}

/*******************************************************************
* 名称：                UART0_Set
* 功能：                设置串口数据位，停止位和效验位
* 入口参数：        fd        串口文件描述符
*                              speed     串口速度
*                              flow_ctrl   数据流控制
*                           databits   数据位   取值为 7 或者8
*                           stopbits   停止位   取值为 1 或者2
*                           parity     效验类型 取值为N,E,O,,S
*出口参数：          正确返回为1，错误返回为0
*******************************************************************/
int UART0_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity)
{

  int   i;
  int   status;
  int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};
  int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};

  struct termios options;

  /*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.
  */
  if  ( tcgetattr( fd, &options)  !=  0)
  {
    dbprintf("SetupSerial \r\n");
    return (FALSE);
  }

  //设置串口输入波特率和输出波特率
  for ( i = 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
  {
    if  (speed == name_arr[i])
    {
      cfsetispeed(&options, speed_arr[i]);
      cfsetospeed(&options, speed_arr[i]);
    }
  }

  //修改控制模式，保证程序不会占用串口
  options.c_cflag |= CLOCAL;
  //修改控制模式，使得能够从串口中读取输入数据
  options.c_cflag |= CREAD;

  //设置数据流控制
  switch (flow_ctrl)
  {

  case 0 ://不使用流控制
    options.c_cflag &= ~CRTSCTS;
    break;

  case 1 ://使用硬件流控制
    options.c_cflag |= CRTSCTS;
    break;
  case 2 ://使用软件流控制
    options.c_cflag |= IXON | IXOFF | IXANY;
    break;
  }
  //设置数据位
  //屏蔽其他标志位
  options.c_cflag &= ~CSIZE;
  switch (databits)
  {
  case 5    :
    options.c_cflag |= CS5;
    break;
  case 6    :
    options.c_cflag |= CS6;
    break;
  case 7    :
    options.c_cflag |= CS7;
    break;
  case 8:
    options.c_cflag |= CS8;
    break;
  default:
    dbprintf("Unsupported data size\n");
    return (FALSE);
  }
  //设置校验位
  switch (parity)
  {
  case 'n':
  case 'N': //无奇偶校验位。
    options.c_cflag &= ~PARENB;
    options.c_iflag &= ~INPCK;
    break;
  case 'o':
  case 'O'://设置为奇校验
    options.c_cflag |= (PARODD | PARENB);
    options.c_iflag |= INPCK;
    break;
  case 'e':
  case 'E'://设置为偶校验
    options.c_cflag |= PARENB;
    options.c_cflag &= ~PARODD;
    options.c_iflag |= INPCK;
    break;
  case 's':
  case 'S': //设置为空格
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    break;
  default:
    dbprintf("Unsupported parity\n");
    return (FALSE);
  }
  // 设置停止位
  switch (stopbits)
  {
  case 1:
    options.c_cflag &= ~CSTOPB; break;
  case 2:
    options.c_cflag |= CSTOPB; break;
  default:
    dbprintf("Unsupported stop bits\n");
    return (FALSE);
  }

  //修改输出模式，原始数据输出
  options.c_oflag &= ~OPOST;

  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//我加的
//options.c_lflag &= ~(ISIG | ICANON);

  //设置等待时间和最小接收字符
  options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */
  options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */

  //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读
  tcflush(fd, TCIFLUSH);

  //激活配置 (将修改后的termios数据设置到串口中）
  if (tcsetattr(fd, TCSANOW, &options) != 0)
  {
    dbprintf("com set error!\n");
    return (FALSE);
  }
  return (TRUE);
}


/*******************************************************************
* 名称：                  UART0_Recv
* 功能：                接收串口数据
* 入口参数：        fd                  :文件描述符
*                              rcv_buf     :接收串口中数据存入rcv_buf缓冲区中
*                              data_len    :一帧数据的长度
* 出口参数：        正确返回为1，错误返回为0
*******************************************************************/
int UART0_Recv(int fd, char *rcv_buf, int data_len)
{
  int len;

  len = read(fd, rcv_buf, data_len);
  
  return len;

}
/********************************************************************
* 名称：                  UART0_Send
* 功能：                发送数据
* 入口参数：        fd                  :文件描述符
*                              send_buf    :存放串口发送数据
*                              data_len    :一帧数据的个数
* 出口参数：        正确返回为1，错误返回为0
*******************************************************************/
int UART0_Send(int fd, char *send_buf, int data_len)
{
  int len = 0;

  tcflush(fd, TCOFLUSH);
  
  len = write(fd, send_buf, data_len);
  if (len == data_len )
  {
    return len;
  }
  else
  {
    tcflush(fd, TCOFLUSH);
    return FALSE;
  }

}





int scan_UART0_Send(int fd, char *send_buf, int data_len)
{
  int res;
  char ch = 0;
  int i;
  char *send_data = NULL;
  int send_data_len = 0;

  send_data_len = data_len+5;

  send_data = (char *)malloc(send_data_len);
  if (send_data == NULL)
  {
    return -1;
  }

  *send_data = 0x02;
  *(send_data+1) = ((send_data_len-3)>>8)&0xff;
  *(send_data+2) = (send_data_len-3)&0xff;

  for(i = 0;i<data_len;i++)
  {
    ch ^=*(send_buf+i);
  }

  memcpy(send_data+3,send_buf,data_len);

  *(send_data+send_data_len-2) = ch;

  *(send_data+send_data_len-1) = 0x03;

  res = UART0_Send(fd,send_data,send_data_len);

  free(send_data);

  return res;

}



int scan_UART0_Send1(int fd, char *send_buf, int data_len)
{
  int res;
  char ch = 0;
  int i;
  char *send_data = NULL;
  int send_data_len = 0;

  send_data_len = data_len+2;

  send_data = (char *)malloc(send_data_len);
  if (send_data == NULL)
  {
    return -1;
  }

 

  memcpy(send_data,send_buf,data_len);

  *(send_data+send_data_len-2) = 0x0D;

  *(send_data+send_data_len-1) = 0x0A;

  res = UART0_Send(fd,send_data,send_data_len);

  free(send_data);

  return res;

}



int scan_deal_uart_msg(int fd,char *uart_msg)
{
    char cmd_code[CMD_CODE_LEN+1] = {0};
    char *p = NULL;

    if(strcmp(uart_msg,"?")==0)
    {
        UART0_Send(fd,"!",1);
        return 0;
    }

    
    p=strstr(uart_msg,COMPANY_NAME);
    if(p == NULL)
    {
        return -1;
    }

    dbprintf("p = [%s]\r\n",p);

    p = p+strlen(COMPANY_NAME);

    
    dbprintf("p = [%s]\r\n",p);

    memcpy(cmd_code,p,CMD_CODE_LEN);
    
    
    dbprintf("cmd_code = [%s]\r\n",cmd_code);


    if(deal_cmd_code(cmd_code,p)==0)
    {
        UART0_Send(fd,"/x06",1);
    }
    else
    {
        UART0_Send(fd,"/x15",1);
    }
    


    return 0;
}






