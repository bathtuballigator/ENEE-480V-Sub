#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>

#include <libcamera/libcamera.h>

using namespace libcamera;
using namespace std::chrono_literals;

int main() {
  // Code to follow

  static std::shared_ptr<Camera> camera;
  std::unique_ptr<CameraManager> cm = std::make_unique<CameraManager>();
  cm->start();

  for (auto const &camera : cm->cameras())
    std::cout << camera->id() << std::endl;

  auto cameras = cm->cameras();
  if (cameras.empty()) {
    std::cout << "No cameras were identified on the system." << std::endl;
    cm->stop();
    return EXIT_FAILURE;
  }

  std::string cameraId = cameras[0]->id();

  auto my_camera = cm->get(cameraId);
  std::cout << "My camera: " << my_camera << std::endl;
  /*
   * Note that `camera` may not compare equal to `cameras[0]`.
   * In fact, it might simply be a `nullptr`, as the particular
   * device might have disappeared (and reappeared) in the meantime.
   */

  return 0;
}
