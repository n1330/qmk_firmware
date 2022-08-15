MOUSEKEY_ENABLE = no    # Mouse keys
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
OLED_ENABLE     = no
# OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
TAP_DANCE_ENABLE = yes

# naginata
UNICODE_ENABLE = yes
SRC +=    naginata_v14.c
EXTRAFLAGS += -flto
