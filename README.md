# VEML7700 driver for Mongoose OS

## Overview

Provides a driver for the VEML7700 ambient light sensor.

Includes automatic gain / interval adjustment algorithm.

## Example

```
struct mgos_veml7700 *s_veml7700 = NULL;

void veml7700_timer(void *arg) {
  float lux = mgos_veml7700_read_lux(s_veml7700, true /* adjust */);
  if (lux >= 0) {
    LOG(LL_INFO, ("%.2f lux", lux));
  }
  (void) arg;
}
...
  if (mgos_veml7700_detect(mgos_i2c_get_bus(0))) {
    s_veml7700 = mgos_veml7700_create(mgos_i2c_get_bus(0));
    bool res = mgos_veml7700_set_cfg(
        s_veml7700,
        MGOS_VEML7700_CFG_ALS_IT_100 | MGOS_VEML7700_CFG_ALS_GAIN_1,
        MGOS_VEML7700_PSM_0);
    LOG(LL_INFO, ("Detected VEML7700, config %d", res));
    mgos_set_timer(100, MGOS_TIMER_REPEAT, veml7700_timer, NULL);
  }

```

## Links

 * [Datasheet](https://media.digikey.com/pdf/Data%20Sheets/Vishay%20Semiconductors/VEML7700.pdf)
 * [Application note](https://www.vishay.com/docs/84323/designingveml7700.pdf)
