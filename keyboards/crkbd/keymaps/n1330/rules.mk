CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
LTO_ENABLE      = yes

# naginata
UNICODE_ENABLE = yes
SRC +=    naginata_v14.c
EXTRAFLAGS += -flto
