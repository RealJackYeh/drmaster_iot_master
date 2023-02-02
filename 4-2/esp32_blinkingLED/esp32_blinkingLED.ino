#define BLINK_GPIO (gpio_num_t)12

void setup() {
  // put your setup code here, to run once:
  gpio_pad_select_gpio(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void loop() {
  gpio_set_level(BLINK_GPIO, 0);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  gpio_set_level(BLINK_GPIO, 1);
  vTaskDelay(1000 / portTICK_PERIOD_MS);  
}
