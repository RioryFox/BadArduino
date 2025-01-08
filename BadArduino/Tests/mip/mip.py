import network
import mip
import time

# Задайте свои данные Wi-Fi
ssid = 'Tenda_24A6C0'
password = '26051976'

# Подключение к Wi-Fi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

print('Connecting to Wi-Fi...', end=' ')
while not wlan.isconnected():
    time.sleep(1)  # Задержка для предотвращения перегрузки
    print('.', end=' ')
print('Connection successful!')

# Установка библиотек
try:
    mip.install('micropython-ssd1306')
    mip.install('micropython-sdcard')
    print('Libraries downloaded successfully!')
except Exception as e:
    print('Error downloading libraries:', e)
