using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GraphicControl.Interface;
using Microsoft.DirectX;
using GraphicControl;

namespace GraphicControl
{
    public class MoveActionObject : IActionObject
    {
        private int Direction;
        public MoveActionObject(int Dir)
        {
            Direction = Dir;
        }
        
        public void DoAction()
        {
            GraphicManager.GetManager().RobotRealMove(Direction);
        }

    }

    public class CreateActionObject : IActionObject
    {
        private Vector3 CreatePos;
        private int Kind;
        public CreateActionObject(Vector3 Pos , int ObjKind)
        {
            CreatePos = Pos;
            Kind = ObjKind;
        }

        public void DoAction()
        {
            GraphicManager.GetManager().RealCreateObj(Kind, CreatePos.X, CreatePos.Z);
        }
    }
}
