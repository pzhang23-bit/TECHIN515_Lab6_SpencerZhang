#include <driver/i2s.h>

#define I2S_WS  2
#define I2S_SCK 44
#define I2S_SD  43

void setup() {
  Serial.begin(115200);
  
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 512,
  };
  i2s_pin_config_t pins = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD,
  };
  i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pins);
}

void loop() {
  int32_t buf[256];
  size_t bytes_read;
  i2s_read(I2S_NUM_0, buf, sizeof(buf), &bytes_read, portMAX_DELAY);
  
  int32_t sample = buf[0] >> 8; // 右移8位取有效数据
  Serial.println(sample);
  delay(10);
}