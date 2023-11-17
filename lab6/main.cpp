#include <libusb-1.0/libusb.h>
#include <cstdio>

void printData(libusb_device *dev) {
    libusb_device_descriptor desc; // дескриптор устройства
    libusb_device_handle *handle = nullptr; // хэндл устройства
    unsigned char str[256]; // строка для хранения серийного номера

    int r = libusb_get_device_descriptor(dev, &desc); // получить дескриптор
    if (r < 0) {
        fprintf(stderr,"Ошибка: дескриптор устройства не получен, код: %d.\n", r);
        return;
    }

    printf(" %.2x %.4x %.4x ", (int) desc.bDeviceClass, desc.idVendor, desc.idProduct);

    libusb_open(dev, &handle);
    if (handle && desc.iSerialNumber) {
        r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, str, sizeof(str)); 
        if (r > 0) {
            printf("%s", str);
        } else {
            printf("empty");
        }
    } else {
        printf("null");
    }
    putchar('\n');
    libusb_close(handle);
}

int main() {
    libusb_device **devs; // указатель на указатель на устройство, используется для получения списка устройств
    libusb_context *ctx = nullptr; // контекст сессии libusb
    int r; // для возвращаемых значений
    ssize_t countUSBDevices; // число найденных USB-устройств

    r = libusb_init(&ctx); // инициализировать библиотеку libusb, открыть сессию работы с libusb
    if (r < 0) {
        fprintf(stderr,"Ошибка: инициализация не выполнена, код: %d.\n", r);
        return 1;
    }

    // получить список всех найденных USB- устройств
    countUSBDevices = libusb_get_device_list(ctx, &devs);
    if (countUSBDevices < 0) {
        fprintf(stderr, "Ошибка: список USB устройств не получен. Код: %d\n", r);
        return 1;
    }

    printf("найдено устройств: %ld\n", countUSBDevices);
    printf("===========================================================\n");
    printf("|* класс устройства\n");
    printf("|  | * идентификатор производителя\n");
    printf("|  |    | * идентификатор устройства\n");
    printf("|  |    |    | * серийный номер\n");
    printf("+--+----+----+--------------------+\n");

    for (ssize_t i = 0; i < countUSBDevices; i++) {
        printData(devs[i]); // печать параметров устройства
    }
    printf("===========================================================\n");

    libusb_free_device_list(devs, 1); // освободить память, выделенную функцией получения списка устройств
    libusb_exit(ctx); // завершить работу с библиотекой libusb, закрыть сессию работы с libusb

    return 0;
}
