.pragma library

function moveCamera(camera, eye, center, up)
{
    console.log("CameraManagement : moveCamera");
    if (camera && eye && center && up)
    {
        camera.upVector = up;
        camera.setCameraCenter(center);
        camera.setCameraEye(eye);
    }
}
