# Circle Bindings for u8g2
[u8g2](https://github.com/olikraus/u8g2) bindings for [Circle](https://github.com/rsta2/circle), a bare-metal programming environment for Raspberry Pi.

## Getting Started
After following the [intro steps on the Circle project](https://github.com/rsta2/circle#building),
the structure of this project should allow you to clone this repo into
the `app` directory of a fresh Circle checkout:

```bash
git clone https://github.com/rsta2/circle.git
cd circle/app
rm -rf *
git clone https://github.com/konistehrad/u8g2_circle.git .
./makeall
```

Circle documentation should be followed for uploading / flashing / copying
the kernel artifact to your Raspberry Pi.

## What's Working
- Hardware I2C support via a HAL object

## What's Left
- Hardware SPI support
- Bit-banging support
- Testing u8g2 button bindings

