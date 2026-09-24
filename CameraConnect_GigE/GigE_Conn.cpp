#include <arv.h>
#include <iostream>

int main()
{
    ArvCamera *camera = arv_camera_new(nullptr, nullptr);

    if (!camera) {
        std::cerr << "No GigE Vision camera found\n";
        return 1;
    }

    // Start image acquisition
    arv_camera_start_acquisition(camera, nullptr);

    for (int i = 0; i < 100; i++) {

        ArvBuffer *buffer =
            arv_camera_pop_buffer(camera, 2000000, nullptr);

        if (!buffer)
            continue;

        size_t size;
        const void *data = arv_buffer_get_data(buffer, &size);

        // 'data' contains the raw image buffer.
        // 'size' is the number of bytes.
        const uint8_t *bytes =
            static_cast<const uint8_t *>(data);

        std::cout << "Received "
                  << size
                  << " bytes\n";

        // Example: access first pixel byte
        uint8_t first_byte = bytes[0];

        std::cout << "First byte: "
                  << static_cast<int>(first_byte)
                  << '\n';

        arv_camera_push_buffer(camera, buffer, nullptr);
    }

    arv_camera_stop_acquisition(camera, nullptr);
    g_object_unref(camera);

    return 0;
}
