#include <arv.h>

#include <cstdint>
#include <iostream>

constexpr int NUM_STORED_FRAMES = 4;
constexpr int NUM_FRAMES = 100;

int main()
{
    GError *error = nullptr;

    // ------------------------------------------------------------
    // Initialize Aravis
    // ------------------------------------------------------------

    arv_update_device_list();

    guint num_cameras = arv_get_n_devices();

    if (num_cameras == 0) {
        std::cerr << "Error: No GigE Vision cameras found.\n";
        return 1;
    }

    std::cout << "Found " << num_cameras << " camera(s).\n";

    // ------------------------------------------------------------
    // Create camera
    // ------------------------------------------------------------

    ArvCamera *camera = arv_camera_new(nullptr, nullptr);

    if (camera == nullptr) {
        std::cerr << "Error: Could not create Aravis camera object.\n";
        return 1;
    }

    // ------------------------------------------------------------
    // Get camera information
    // ------------------------------------------------------------

    const char *vendor =
        arv_camera_get_vendor_name(camera, nullptr);

    const char *model =
        arv_camera_get_model_name(camera, nullptr);

    if (vendor)
        std::cout << "Vendor: " << vendor << '\n';

    if (model)
        std::cout << "Model: " << model << '\n';

    // ------------------------------------------------------------
    // Get image dimensions
    // ------------------------------------------------------------

    gint width;
    gint height;

    arv_camera_get_sensor_size(camera, &width, &height, &error);

    if (error != nullptr) {
        std::cerr << "Error getting image size: "
                  << error->message << '\n';

        g_error_free(error);
        error = nullptr;

        g_object_unref(camera);
        return 1;
    }

    

    if (error != nullptr) {
        std::cerr << "Error getting image height: "
                  << error->message << '\n';

        g_error_free(error);
        error = nullptr;

        g_object_unref(camera);
        return 1;
    }

    std::cout << "Image size: "
              << width << " x " << height << '\n';

    // ------------------------------------------------------------
    // Get payload size
    //
    // This is the amount of memory required for one frame.
    // It is preferable to width * height because the camera
    // may use Mono16, RGB, packed formats, padding, etc.
    // ------------------------------------------------------------

    guint payload =
        arv_camera_get_payload(camera, &error);

    if (error != nullptr) {
        std::cerr << "Error getting payload size: "
                  << error->message << '\n';

        g_error_free(error);
        error = nullptr;

        g_object_unref(camera);
        return 1;
    }

    std::cout << "Payload size: "
              << payload << " bytes\n";

    // ------------------------------------------------------------
    // Create stream
    // ------------------------------------------------------------

    ArvStream *stream =
        arv_camera_create_stream(
            camera,
            nullptr,
            nullptr,
            &error);

    if (error != nullptr) {
        std::cerr << "Error creating stream: "
                  << error->message << '\n';

        g_error_free(error);
        error = nullptr;

        g_object_unref(camera);
        return 1;
    }

    if (stream == nullptr) {
        std::cerr << "Error: Aravis returned a null stream.\n";

        g_object_unref(camera);
        return 1;
    }

    // ------------------------------------------------------------
    // Allocate buffers
    //
    // Aravis needs buffers in the stream before acquisition begins.
    // ------------------------------------------------------------

    for (int i = 0; i < NUM_STORED_FRAMES; ++i) {

        ArvBuffer *buffer =
            arv_buffer_new(payload, nullptr);

        if (buffer == nullptr) {
            std::cerr << "Error: Could not allocate buffer "
                      << i << ".\n";

            g_object_unref(stream);
            g_object_unref(camera);
            return 1;
        }

        arv_stream_push_buffer(stream, buffer);
    }

    // ------------------------------------------------------------
    // Start acquisition
    // ------------------------------------------------------------

    arv_camera_start_acquisition(camera, &error);

    if (error != nullptr) {
        std::cerr << "Error starting acquisition: "
                  << error->message << '\n';

        g_error_free(error);
        error = nullptr;

        g_object_unref(stream);
        g_object_unref(camera);
        return 1;
    }

    std::cout << "Acquisition started.\n";

    // ------------------------------------------------------------
    // Receive frames
    // ------------------------------------------------------------

    for (int i = 0; i < NUM_FRAMES; ++i) {

        ArvBuffer *buffer =
            arv_stream_timeout_pop_buffer(stream, 2000000);

        if (buffer == nullptr) {
            std::cerr << "Warning: Timeout waiting for frame "
                      << i << ".\n";

            continue;
        }

        // --------------------------------------------------------
        // Check buffer status
        // --------------------------------------------------------

        ArvBufferStatus status =
            arv_buffer_get_status(buffer);

        if (status != ARV_BUFFER_STATUS_SUCCESS) {

            std::cerr << "Frame " << i
                            << " received with error status: "
                            << static_cast<int>(status)
                            << '\n';

            // Return buffer to stream
            arv_stream_push_buffer(stream, buffer);

            continue;
        }

        // --------------------------------------------------------
        // Get image data
        // --------------------------------------------------------

        size_t size = 0;

        const void *data =
            arv_buffer_get_data(buffer, &size);

        if (data == nullptr) {

            std::cerr << "Error: Frame "
                      << i << " contains no data.\n";

            arv_stream_push_buffer(stream, buffer);

            continue;
        }

        const uint8_t *bytes =
            static_cast<const uint8_t *>(data);

        // --------------------------------------------------------
        // Print frame information
        // --------------------------------------------------------

        std::cout << "Frame " << i
                  << ": "
                  << size
                  << " bytes";

        std::cout << ", first byte = "
                  << static_cast<unsigned int>(bytes[0])
                  << '\n';

        // --------------------------------------------------------
        // IMPORTANT:
        //
        // Process/copy the image data here.
        //
        // The buffer belongs to Aravis and must eventually be
        // returned to the stream.
        // --------------------------------------------------------

        arv_stream_push_buffer(stream, buffer);
    }

    // ------------------------------------------------------------
    // Stop acquisition
    // ------------------------------------------------------------

    arv_camera_stop_acquisition(camera, &error);

    if (error != nullptr) {
        std::cerr << "Error stopping acquisition: "
                  << error->message << '\n';

        g_error_free(error);
        error = nullptr;
    }

    std::cout << "Acquisition stopped.\n";

    // ------------------------------------------------------------
    // Cleanup
    // ------------------------------------------------------------

    g_object_unref(stream);
    g_object_unref(camera);

    return 0;
}