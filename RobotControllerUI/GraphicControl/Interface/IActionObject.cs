using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX;

namespace GraphicControl.Interface
{
    /// <summary>
    /// 로봇 객체가 하는 행동 오브젝트의 인터페이스
    /// </summary>
    public interface IActionObject
    {
        /// <summary>
        /// 액션 실행
        /// </summary>
        void DoAction();
        
    }
}
