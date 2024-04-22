#include <stdio.h>

// CRC-32 Algorithm (reuse from previous code)
unsigned int crc32(const unsigned char* data, size_t length) {
    unsigned int crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else {
                crc >>= 1;
            }
        }
    }
    return crc ^ 0xFFFFFFFF;
}

void test_crc32(const char* description, const unsigned char* data, size_t length) {
    unsigned int crc = crc32(data, length);
    printf("%s: %08X\n", description, crc);
}

int main() {
    // ȫ0����
    unsigned char all_zero[16] = { 0 };
    test_crc32("ȫ0����", all_zero, sizeof(all_zero));

    // ȫ1����
    unsigned char all_one[16];
    for (int i = 0; i < 16; i++) {
        all_one[i] = 0xFF;
    }
    test_crc32("ȫ1����", all_one, sizeof(all_one));

    // �ظ�ģʽ����
    unsigned char pattern[16] = { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,
                                 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 };
    test_crc32("�ظ�ģʽ����", pattern, sizeof(pattern));

    return 0;
}
