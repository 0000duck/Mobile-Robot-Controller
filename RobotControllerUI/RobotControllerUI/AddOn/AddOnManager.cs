using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RobotControllerUI;

namespace RobotControllerUI.AddOn
{
    /// <summary>
    /// Addon 통합 관리 매니져
    /// </summary>
    public class AddOnManager
    {
        private static AddOnManager Instance = null;

        private AddOnManager()
        { }

        /// <summary>
        /// 싱글톤 클래스 접근자
        /// </summary>
        /// <returns>인스턴스 반환</returns>
        public static AddOnManager GetManager()
        {
            if (Instance == null)
            {
                Instance = new AddOnManager();
            }
            return Instance;
        }
    }
}
