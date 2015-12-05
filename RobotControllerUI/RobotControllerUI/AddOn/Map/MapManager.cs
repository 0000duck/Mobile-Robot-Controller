using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotControllerUI.AddOn.Map
{
    public class MapManager
    {
        List<Spot> HazardList;
        Spot mapSize;
        MapModel Map;

        public const int HAZARD = GraphicControl.DrawObject.ModelManager.HAZARD;
        public const int COLOR = GraphicControl.DrawObject.ModelManager.COLOR;
        

        public Spot MapSize
        {
            get; protected set;
        }
        public MapManager()
        {
            HazardList = new List<Spot>();
        }
        /// <summary>
        /// 맵 모델을 만들어주는함수
        /// </summary>
        public void CreateMapModel()
        {
            Map = new MapModel((int)MapSize.x, (int)MapSize.y);
        }
        //public void Analyze
        /// <summary>
        /// ColorBlob을 추가하는 함수
        /// </summary>
        public void AddColorBlob(int x , int y)
        {
            Map.AddObj(x, y, COLOR);
        }
        /// <summary>
        /// Hazard를 추가하는 함수
        /// </summary>
        /// <param name="Hazard"></param>
        public void AddHazardPoint(Spot Hazard)
        {
            if (Hazard == null || Map ==null) return;
            HazardList.Add(Hazard);
            Map.AddObj((int)Hazard.x, (int)Hazard.y, HAZARD);

        }
        /// <summary>
        /// 앞쪽 노드를 반환(미완성)
        /// </summary>
        /// <param name="CurruntX"></param>
        /// <param name="CurruntY"></param>
        /// <param name="Direction"></param>
        /// <returns></returns>
        [Obsolete("미완성 메소드 방향 구현하고 구현할것")]
        public MapNode GetNearMapNode(int CurruntX , int CurruntY , int Direction)
        {
            return Map[CurruntY , CurruntX]; 
        }
        
    }
}
