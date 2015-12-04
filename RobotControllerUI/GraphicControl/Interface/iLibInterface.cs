using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using GraphicControl;
namespace GraphicControl.Interface
{
    
    [Guid("ADE697B3-B420-4C4A-B84A-B106DD0D3038")]
    interface GraphicInterface
    {
        
       
            void MoveRobot(int Direction);
            void CreateObj(int KindObj, float X2d, float Y2d);
            void Start();
            void End();
  
    }
    
        [Guid("6D1EA255-73D8-4480-B75D-4EC5387293C9")]
        public class GraphicInterfaceImplement : GraphicInterface
    {
            public void MoveRobot(int Direction)
            {
                GraphicManager.GetManager().MoveRobot(Direction);
            }
            /// <summary>
            /// type을 받아서 객체 생성
            /// </summary>
            /// <param name="KindObj"></param>
            public void CreateObj(int KindObj, float X2d, float Y2d)
            { }
            /// <summary>
            /// 탐색이 시작됨을 알려줌
            /// </summary>
            public void Start()
            { }
            /// <summary>
            /// 탐색이 종료됨을 알려줌
            /// </summary>
            public void End()
            { }
           
        }
       
}
