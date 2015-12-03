using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX;
using System.Windows.Forms;
using Microsoft.DirectX.Direct3D;
using GraphicControl.DrawObject;

namespace GraphicControl
{
    /// <summary>
    /// DirectX Camera
    /// </summary>
    class Camera
    {
        Device dev;
        Vector3 Position;
        Vector3 LookAt;
        Vector3 Up;
        public Camera(Device dev)
        {
            this.dev = dev;
            Position = new Vector3(0.0f, 3.0f, -5.0f);
            LookAt = new Vector3(0, 0, 0);
            Up = new Vector3(0, 1, 0);

        }
        /// <summary>
        /// 0,0,0 에 고정되있는 카메라모드
        /// </summary>
        public void CameraUpdate()
        {
            dev.Transform.View = Matrix.LookAtLH(Position,
                LookAt,
                Up);
        }
        /// <summary>
        /// Target을 Tracking 하는 카메라모드
        /// </summary>
        /// <param name="TargetPos">추적대상의 위치</param>
        public void CameraUpdate(Vector3 TargetPos)
        {
            Vector3 NewCameraPos = Position + TargetPos;
            dev.Transform.View = Matrix.LookAtLH(NewCameraPos,
               TargetPos,
               Up);
        }
    }
}
