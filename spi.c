#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <math.h>

#define R_NOM (100)
#define R_REF (430)

#define RTD_A (3.9083e-3)
#define RTD_B (-5.775e-7)

#define Z1 (-RTD_A)
#define Z2 (RTD_A * RTD_A - (4 * RTD_B)
#define Z3 (4 * RTD_B) / R_NOM)
#define Z4 (2 * RTD_B)

static int fd;

static uint8_t mode = 1;
static uint8_t bits = 8;
static uint32_t speed = 5000000;

float read_rtd() {
    int ret = 0;

    uint8_t tx[] = {0x01, 0x00, 0x00};
    uint8_t rx[3] = {0,};
    struct spi_ioc_transfer tr = {
	.tx_buf = (unsigned long)tx,
	.rx_buf = (unsigned long)rx,
	.len = 3,
	.delay_usecs = 0,
	.speed_hz = speed,
	.bits_per_word = bits,
    };
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    float r = ((rx[1] << 7) + (rx[2] >> 1)) / 32768.0 * R_REF;
    return r;
}

float read_temp() {
    float t = (sqrt(Z2 + (Z3*read_rtd())) + Z1) / Z4;
    t = t * 9/5 + 32;
    printf("%f\n", t);
    return t;
}

int main(void) {
    int ret = 0;

    char buf[128];
    printf("spi\n");

    fd = open("/dev/spidev0.0", O_RDWR);
    printf("fd %d\n", fd);

    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    printf("wr_mode %d %d\n", ret, mode);
    mode = 0;
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    printf("rd_mode %d %d\n", ret, mode);

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    printf("wr_bits %d %d\n", ret, bits);
    bits = 0;
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    printf("rd_bits %d %d\n", ret, bits);

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    printf("wr_speed %d %d\n", ret, speed);
    speed = 0;
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    printf("rd_speed %d %d\n", ret, speed);

    uint8_t tx1[] = {0x80, 0xd0};
    uint8_t rx1[128] = {0,};
    struct spi_ioc_transfer tr1 = {
	.tx_buf = (unsigned long)tx1,
	.rx_buf = (unsigned long)rx1,
	.len = 2,
	.delay_usecs = 0,
	.speed_hz = speed,
	.bits_per_word = bits,
    };
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr1);
    printf("xfer %d\n", ret);
    for (int i=1; i<tr1.len; i++) {
        printf("%02x ", rx1[i]);
    }
    printf("\n");

    sleep(1);

    uint8_t tx[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t rx[128] = {0,};
    struct spi_ioc_transfer tr = {
	.tx_buf = (unsigned long)tx,
	.rx_buf = (unsigned long)rx,
	.len = 9,
	.delay_usecs = 0,
	.speed_hz = speed,
	.bits_per_word = bits,
    };
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    printf("xfer %d\n", ret);
    for (int i=1; i<tr.len; i++) {
        printf("%02x ", rx[i]);
    }
    printf("\n");

    for (int i=0; i<100; i++) {
        sleep(1);
        read_temp();
    }

    close(fd);

    return 0;
}
