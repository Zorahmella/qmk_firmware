POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
DEFERRED_EXEC_ENABLE = yes
CUSTOM_MATRIX = lite
SRC += \
	matrix.c\
	analog.c\
	honeydew.c
QUANTUM_LIB_SRC += spi_master.c
