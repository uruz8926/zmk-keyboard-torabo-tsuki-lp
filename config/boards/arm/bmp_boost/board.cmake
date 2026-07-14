board_runner_args(nrfjprog "--nrf-family=NRF52")
board_runner_args(nrfutil "--family=NRF52840")

include(${ZEPHYR_BASE}/boards/arm/nice_nano_v2/board.cmake)
