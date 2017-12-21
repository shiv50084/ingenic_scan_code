#ifndef __LINUX_SPI_JZ_H
#define __LINUX_SPI_JZ_H

#include <mach/jzdma.h>

/*************************************************************************
 * SSI (Synchronous Serial Interface)
 *************************************************************************/
/* n = 0, 1 (SSI0, SSI1) */
#define	SSI_DR			0x000
#define	SSI_CR0			0x004
#define	SSI_CR1			0x008
#define	SSI_SR			0x00C
#define	SSI_ITR			0x010
#define	SSI_ICR			0x014
#define	SSI_GR			0x018
#define	SSI_RCNT		0x01C

/* SSI Data Register (SSI_DR) */
#define	DR_GPC_BIT		0
#define	DR_GPC_MASK		(0x1ff << SSI_DR_GPC_BIT)

/* SSI Control Register 0 (SSI_CR0) */
#define CR0_TENDIAN_BIT		18
#define CR0_TENDIAN_MASK	(3 << CR0_TENDIAN_BIT)
#define CR0_RENDIAN_BIT		16
#define CR0_RENDIAN_MASK	(3 << CR0_RENDIAN_BIT)
#define CR0_SSIE		(1 << 15)
#define CR0_TIE			(1 << 14)
#define CR0_RIE			(1 << 13)
#define CR0_TEIE		(1 << 12)
#define CR0_REIE		(1 << 11)
#define CR0_LOOP		(1 << 10)
#define CR0_RFINE		(1 << 9)
#define CR0_RFINC		(1 << 8)
#define CR0_EACLRUN		(1 << 7) /* hardware auto clear underrun when TxFifo no empty */
#define CR0_FSEL		(1 << 6)
#define CR0_VRCNT		(1 << 4)
#define CR0_TFMODE		(1 << 3)
#define CR0_TFLUSH		(1 << 2)
#define CR0_RFLUSH		(1 << 1)
#define CR0_DISREV		(1 << 0)

/* SSI Control Register 1 (SSI_CR1) */
#define CR1_FRMHL_BIT		30
#define CR1_FRMHL_MASK		(0x3 << CR1_FRMHL_BIT)
#define CR1_FRMHL_CELOW_CE2LOW	(0 << CR1_FRMHL_BIT) /* SSI_CE_ is low valid and SSI_CE2_ is low valid */
#define CR1_FRMHL_CEHIGH_CE2LOW	(1 << CR1_FRMHL_BIT) /* SSI_CE_ is high valid and SSI_CE2_ is low valid */
#define CR1_FRMHL_CELOW_CE2HIGH	(2 << CR1_FRMHL_BIT) /* SSI_CE_ is low valid  and SSI_CE2_ is high valid */
#define CR1_FRMHL_CEHIGH_CE2HIGH	(3 << CR1_FRMHL_BIT) /* SSI_CE_ is high valid and SSI_CE2_ is high valid */
#define CR1_TFVCK_BIT		28
#define CR1_TFVCK_MASK		(0x3 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_0		  (0 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_1		  (1 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_2		  (2 << CR1_TFVCK_BIT)
  #define CR1_TFVCK_3		  (3 << CR1_TFVCK_BIT)
#define CR1_TCKFI_BIT		26
#define CR1_TCKFI_MASK		(0x3 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_0		  (0 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_1		  (1 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_2		  (2 << CR1_TCKFI_BIT)
  #define CR1_TCKFI_3		  (3 << CR1_TCKFI_BIT)
#define CR1_ITFRM		(1 << 24)
#define CR1_UNFIN		(1 << 23)
#define CR1_FMAT_BIT		20
#define CR1_FMAT_MASK		(0x3 << CR1_FMAT_BIT)
  #define CR1_FMAT_SPI		  (0 << CR1_FMAT_BIT) /* Motorola¡¯s SPI format */
  #define CR1_FMAT_SSP		  (1 << CR1_FMAT_BIT) /* TI's SSP format */
  #define CR1_FMAT_MW1		  (2 << CR1_FMAT_BIT) /* National Microwire 1 format */
  #define CR1_FMAT_MW2		  (3 << CR1_FMAT_BIT) /* National Microwire 2 format */
#define CR1_TTRG_BIT		16 /* SSI1 TX trigger */
#define CR1_TTRG_MASK		(0xf << CR1_TTRG_BIT)
#define CR1_MCOM_BIT		12
#define CR1_MCOM_MASK		(0xf << CR1_MCOM_BIT)
//  #define CR1_MCOM_BIT(NO)	  (##NO## << CR1_MCOM_BIT) /* N-bit command selected */
#define CR1_RTRG_BIT		8 /* SSI RX trigger */
#define CR1_RTRG_MASK		(0xf << CR1_RTRG_BIT)
#define CR1_FLEN_BIT		3
#define CR1_FLEN_MASK		(0x1f << CR1_FLEN_BIT)
  #define CR1_FLEN_2BIT		  (0x0 << CR1_FLEN_BIT)
#define CR1_PHA			(1 << 1)
#define CR1_POL			(1 << 0)

/* SSI Status Register (SSI_SR) */
#define SR_TFIFONUM_BIT		16
#define SR_TFIFONUM_MASK	(0xff << SR_TFIFONUM_BIT)
#define SR_RFIFONUM_BIT		8
#define SR_RFIFONUM_MASK	(0xff << SR_RFIFONUM_BIT)
#define SR_END			(1 << 7)
#define SR_BUSY			(1 << 6)
#define SR_TFF			(1 << 5)
#define SR_RFE			(1 << 4)
#define SR_TFHE			(1 << 3)
#define SR_RFHF			(1 << 2)
#define SR_UNDR			(1 << 1)
#define SR_OVER			(1 << 0)

/* SSI Interval Time Control Register (SSI_ITR) */
#define	ITR_CNTCLK		(1 << 15)
#define ITR_IVLTM_BIT		0
#define ITR_IVLTM_MASK		(0x7fff << ITR_IVLTM_BIT)



#define R_MODE			0x1
#define W_MODE			0x2
#define RW_MODE			(R_MODE | W_MODE)

#define R_DMA			0x4
#define W_DMA			0x8
#define RW_DMA			(R_DMA |W_DMA)

#define SPI_DMA_ACK		0x1

#define SPI_DMA_ERROR  		-3
#define SPI_CPU_ERROR		-4

#define SPI_COMPLETE		5

#define JZ_SSI_MAX_FIFO_ENTRIES 	128
#define JZ_SSI_DMA_BURST_LENGTH 	16

#define FIFO_W8			8
#define FIFO_W16		16
#define FIFO_W32		32

#define SPI_BITS_8		8
#define SPI_BITS_16		16
#define SPI_BITS_32		32

#define SPI_8BITS		1
#define SPI_16BITS		2
#define SPI_32BITS		4


/* tx rx threshold from 0x0 to 0xF */
#define SSI_FULL_THRESHOLD		0xF
#define SSI_TX_FIFO_THRESHOLD		0x1
#define SSI_RX_FIFO_THRESHOLD		(SSI_FULL_THRESHOLD - SSI_TX_FIFO_THRESHOLD)
#define SSI_SAFE_THRESHOLD		0x1

#define CPU_ONCE_BLOCK_ENTRIES 		((SSI_FULL_THRESHOLD-SSI_TX_FIFO_THRESHOLD)*8)

#define MAX_SSI_INTR		10000

#define MAX_SSICDR			63
#define MAX_CGV				255

#define SSI_DMA_FASTNESS_CHNL 	 0   // SSI controller [n] FASTNESS when probe();

#define JZ_NEW_CODE_TYPE

#define BUFFER_SIZE	PAGE_SIZE

#define CONFIG_DMA_ENGINE 1

#define SUSPND    (1<<0)
#define SPIBUSY   (1<<1)
#define RXBUSY    (1<<2)
#define TXBUSY    (1<<3)

struct jz_spi {
	/* bitbang has to be first */
	struct spi_bitbang	bitbang;
	struct clk		*clk_gate;
	struct clk		*clk;
	unsigned int		clk_flag;
	unsigned int		set_clk_flag;
	struct completion	done;
	struct completion	done_rx;
	struct completion	done_tx_dma;
	struct completion	done_rx_dma;

	spinlock_t		lock;
	spinlock_t		txrx_lock;

	unsigned int		state;

	u8			chnl;
	u8			rw_mode;
	u8			spi_mode;
	u8			use_dma;
	u8			is_first;

	u8			bits_per_word;		/*8 or 16 (or 32)*/
	u8			transfer_unit_size;	/* 1 or 2 (or 4) */
	u8			tx_trigger;		/* 0-128 */
	u8			rx_trigger;		/* 0-128 */
	u8			dma_tx_unit;		/* 1 or 2 or 4 or 16 or 32*/
	u8			dma_rx_unit;		/* 1 or 2 or 4 or 16 or 32*/
	u8			txfifo_width;
	u8			rxfifo_width;
	u32			fifodepth;

	/* data buffers */
	const u8		*tx;
	u8			*rx;

	/* temp buffers */
	void			*buffer;
	dma_addr_t		buffer_dma;

	void __iomem		*iomem;
	unsigned long		phys;
	int			 irq;
	u32			 len;
	u32			 rlen;	  /* receive len */
	u32			 count;   /* sent count */
	enum jzdma_type     	 dma_type;
	u32			 dma_flag;

	void			(*set_cs)(struct jz_spi_info *spi, u8 cs, unsigned int pol);

	/* functions to deal with different size buffers */
	u32 (*get_rx) (struct jz_spi *);
	u32 (*get_tx) (struct jz_spi *);
	int (*txrx_bufs)(struct spi_device *spi, struct spi_transfer *t);
	irqreturn_t (*irq_callback)(struct jz_spi *);

#ifdef CONFIG_DMA_ENGINE
	struct dma_chan 	*txchan;
	struct dma_chan 	*rxchan;
	struct scatterlist  	*sg_rx;	/* I/O scatter list */
	struct scatterlist  	*sg_tx;	/* I/O scatter list */
#endif

	unsigned long src_clk;
	unsigned long spi_clk;

	struct jz_intr_cnt *g_jz_intr;

	struct resource		*ioarea;
	struct spi_master	*master;
	struct device		*dev;
	struct jz_spi_info *pdata;
//	struct spi_board_info *pdata;
};


struct jz_intr_cnt{
	int dma_tx_cnt;
	int dma_rx_cnt;
	int ssi_intr_cnt;
	int max_ssi_intr;
	int ssi_txi;
	int ssi_rxi;
	int ssi_eti;
	int ssi_eri;
	int ssi_rlen;
	int dma_tx_err;
	int dma_tx_end;
	int dma_rx_err;
	int dma_rx_end;
};
/* the max number of spi devices */
#define MAX_SPI_DEVICES				10
#define MAX_SPI_HOST				2

#define JZ_SPI_ID_INVALID(ssi_id) ( ((ssi_id) < 0) || ((ssi_id) > (MAX_SPI_HOST - 1)) )

#define MAX_SPI_CHIPSELECT_NUM 		MAX_GPIO_NUM


static inline void spi_writel(struct jz_spi *spi,
			      unsigned short offset, u32 value)
{
	writel(value, spi->iomem + offset);
}

static inline u32 spi_readl(struct jz_spi *spi,
				      unsigned short offset)
{
	return readl(spi->iomem + offset);
}

static inline void set_frmhl(struct jz_spi *spi, unsigned int frmhl)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp = (tmp & ~CR1_FRMHL_MASK) | frmhl;
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void set_spi_clock_phase(struct jz_spi *spi, unsigned int cpha)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp = (tmp & ~CR1_PHA) | (cpha ? CR1_PHA : 0);
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void set_spi_clock_polarity(struct jz_spi *spi,
					  unsigned int cpol)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp = (tmp & ~CR1_POL) | (cpol ? CR1_POL : 0);
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void set_tx_msb(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_TENDIAN_MASK;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void set_tx_lsb(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= (tmp & ~CR0_TENDIAN_MASK) | (0x3 << CR0_TENDIAN_BIT);
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void set_rx_msb(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_RENDIAN_MASK;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void set_rx_lsb(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= (tmp & ~CR0_RENDIAN_MASK) | (0x3 << CR0_RENDIAN_BIT);
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void enable_loopback(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_LOOP;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_loopback(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_LOOP;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void transmit_data(struct jz_spi *spi, u32 value)
{
	spi_writel(spi, SSI_DR, value);
}

static inline void set_frame_length(struct jz_spi *spi, u32 len)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp = (tmp & ~CR1_FLEN_MASK) | (((len) - 2) << CR1_FLEN_BIT);
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void set_tx_trigger(struct jz_spi *spi, u32 val)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp = (tmp & ~CR1_TTRG_MASK) | ((val)/8) << CR1_TTRG_BIT;
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void set_rx_trigger(struct jz_spi *spi, u32 val)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp = (tmp & ~CR1_RTRG_MASK) | ((val)/8) << CR1_RTRG_BIT;
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void enable_txfifo_half_empty_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_TIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_txfifo_half_empty_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_TIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void enable_rxfifo_half_full_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_RIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_rxfifo_half_full_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_RIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void enable_tx_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_TIE | CR0_TEIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_tx_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~(CR0_TIE | CR0_TEIE);
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void enable_rx_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_RIE | CR0_REIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_rx_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~(CR0_RIE | CR0_REIE);
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void enable_tx_error_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_TEIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_tx_error_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_TEIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void enable_rx_error_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_REIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_rx_error_intr(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_REIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void underrun_auto_clear(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_EACLRUN;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void clear_errors(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_SR);
	tmp &= ~(SR_UNDR | SR_OVER);
	spi_writel(spi, SSI_SR, tmp);
}

static inline void set_spi_format(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp &= ~CR1_FMAT_MASK;
	tmp |= CR1_FMAT_SPI;
	tmp &= ~(CR1_TFVCK_MASK | CR1_TCKFI_MASK);
	tmp |= (CR1_TFVCK_0 | CR1_TCKFI_0);
//	tmp |= (CR1_TFVCK_1 | CR1_TCKFI_1);
//	tmp |= (CR1_TFVCK_2 | CR1_TCKFI_2);
//	tmp |= (CR1_TFVCK_3 | CR1_TCKFI_3);
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void enable_receive(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_DISREV;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void disable_receive(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_DISREV;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void flush_fifo(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_TFLUSH | CR0_RFLUSH;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void finish_transmit(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp &= ~CR1_UNFIN;
	spi_writel(spi, SSI_CR1, tmp);
}

static inline void start_transmit(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR1);
	tmp |= CR1_UNFIN;
	spi_writel(spi, SSI_CR1, tmp);
}

static inline int rxfifo_empty(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_RFE;
}

static inline int ssi_busy(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_BUSY;
}

static inline void ssi_disable(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_SSIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void ssi_enable(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_SSIE;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline u32 get_rxfifo_count(struct jz_spi *spi)
{
	return (spi_readl(spi, SSI_SR) & SR_RFIFONUM_MASK) >> SR_RFIFONUM_BIT;
}

static inline void flush_txfifo(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_TFLUSH;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void flush_rxfifo(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_RFLUSH;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline int ssi_underrun(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_UNDR;
}

static inline int ssi_overrun(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_OVER;
}

static inline int ssi_transfer_end(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_END;
}

static inline int tx_error_intr(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_CR0) & CR0_TEIE;
}

static inline int rx_error_intr(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_CR0) & CR0_REIE;
}

static inline int rxfifo_half_full(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_RFHF;
}

static inline int txfifo_half_empty(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_SR) & SR_TFHE;
}

static inline int txfifo_half_empty_intr(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_CR0) & CR0_TIE;
}

static inline int rxfifo_half_full_intr(struct jz_spi *spi)
{
	return spi_readl(spi, SSI_CR0) & CR0_RIE;
}

static inline void select_ce(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp &= ~CR0_FSEL;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void select_ce2(struct jz_spi *spi)
{
	u32 tmp;
	tmp = spi_readl(spi, SSI_CR0);
	tmp |= CR0_FSEL;
	spi_writel(spi, SSI_CR0, tmp);
}

static inline void dump_spi_reg(struct jz_spi *spi)
{
//	printk("SSI_DR	:%08x\n", spi_readl(spi, SSI_DR	));
	printk("SSI_CR0	:%08x\n", spi_readl(spi, SSI_CR0 ));
	printk("SSI_CR1	:%08x\n", spi_readl(spi, SSI_CR1 ));
	printk("SSI_SR	:%08x\n", spi_readl(spi, SSI_SR	));
	printk("SSI_ITR	:%08x\n", spi_readl(spi, SSI_ITR ));
	printk("SSI_ICR	:%08x\n", spi_readl(spi, SSI_ICR ));
	printk("SSI_GR	:%08x\n", spi_readl(spi, SSI_GR	));
	printk("SSI_RCNT:%08x\n", spi_readl(spi, SSI_RCNT));
}

#endif /* __LINUX_SPI_JZ_H */
