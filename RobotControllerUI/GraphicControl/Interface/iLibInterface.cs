using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using GraphicControl;
namespace GraphicControl.Interface
{

    [Guid("91D3BE1B-2A5F-4300-957E-ABE2DC66188F")]
    public interface iLibInterface
    {
        
       
            void MoveRobot(int Direction);
            void CreateObj(int KindObj, float X2d, float Y2d);
            void Start();
            void End();
  
    }
    
        [Guid("6D1EA255-73D8-4480-B75D-4EC5387293C9")]
        public class InterfaceImplement : iLibInterface
    {
            /// <summary>
            /// Robot을 움직이는 함수( Up : 0 Down : 1 Left : 2 Right: 3)
            /// </summary>
            /// <param name="Direction"></param>
            public void MoveRobot(int Direction)
            {
                GraphicManager.GetManager().MoveRobot(Direction);
            }
            /// <summary>
            /// type을 받아서 객체 생성(Hazard :2 Color:3)
            /// </summary>
            /// <param name="KindObj"></param>
            public void CreateObj(int KindObj, float X2d, float Y2d)
            {
                GraphicManager.GetManager().CreateObj(KindObj, X2d, Y2d);
            }
            /// <summary>
            /// 탐색이 시작됨을 알려줌
            /// </summary>
            public void Start()
            {
                GraphicManager.GetManager().Start();
            }
            /// <summary>
            /// 탐색이 종료됨을 알려줌
            /// </summary>
            public void End()
            {
                GraphicManager.GetManager().End();
            }
           
           
        }
       
}
