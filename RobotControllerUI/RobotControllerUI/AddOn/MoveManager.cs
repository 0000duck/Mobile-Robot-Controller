using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotControllerUI.AddOn
{
    public class MoveManager
    {

        Queue<Spot> SearchSpotQueue;
        /// <summary>
        /// 생성자
        /// </summary>
        public MoveManager()
        {
            SearchSpotQueue = new Queue<Spot>();
        }

        /// <summary>
        /// 탐색 큐 초기화
        /// </summary>
        public void InitSearchSpotQueue()
        {
            SearchSpotQueue.Clear();
        }
        /// <summary>
        /// 탐색 큐에 위치를 List로 한번에 추가
        /// </summary>
        /// <param name="SpotList">추가할 SpotList</param>
        public void EnqueueSearchList(List<Spot> SpotList)
        {
            if (SearchSpotQueue == null || SpotList == null) return;

            foreach (Spot S in SpotList)
            {
                SearchSpotQueue.Enqueue(S);
            }
        }
        

    }
}
