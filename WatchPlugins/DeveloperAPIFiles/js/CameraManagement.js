.pragma library

function moveCamera(camera, eye, center, up)
{
    if (camera && eye && center)
    {
        if (up)
            camera.upVector = up;
        console.log("CameraManagement : moveCamera eye " + eye + " center " + center);
        camera.setCameraCenter(center);
        camera.setCameraEye(eye);
    }
}
