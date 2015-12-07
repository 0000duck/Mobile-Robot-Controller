using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotControllerUI.AddOn.Map
{
    public class MapModel
    {
        MapNode[][] MapData;
        Spot MapSize;
        
        /// <summary>
        /// 클래스 인덱서
        /// </summary>
        /// <param name="y"> y 좌표</param>
        /// <param name="x"> x 좌표</param>
        /// <returns></returns>
        public MapNode this[int y ,int x]
        {
            get { return GetMapNode(x,y); }
            protected set { MapData[(int)MapSize.y - y-1][x] = value; }
        }
        /// <summary>
        /// MapModel 생성자
        /// </summary>
        /// <param name="x"> XSize</param>
        /// <param name="y">YSize</param>
        public MapModel(int x, int y)
        {
            MapSize = new Spot(x, y);

            MapData = new MapNode[y][];
            for (int i = 0; i < MapData.GetLength(0); i++)
            {
                MapData[i] = new MapNode[x];
                for (int j = 0; j < MapData.GetLength(1); j++)
                {
                    MapData[i][j] = new MapNode();
                }
            }
            OnMapModelCreate();
        }
        /// <summary>
        /// Map이 생서되었을때 실행되는 콜백함수
        /// Node마다 주변노드들을 등록해준다.
        /// </summary>
        private void OnMapModelCreate()
        {
            for (int y = 0; y < MapData.GetLength(0); y++)
            {
                for (int x = 0; x < MapData.GetLength(1); x++)
                {
                    MapData[y][x].InitNearNode(this[x,y+1],
                        this[x, y - 1],
                        this[x - 1, y],
                        this[x +1, y]); 
                }
            }
        }
        /// <summary>
        /// 특정위치의 노드를 가져오는 함수
        /// </summary>
        /// <param name="x"> x 좌표</param>
        /// <param name="y">y 좌표</param>
        /// <returns>
        /// (예외)인덱스 음수 , 최대범위 초과 >> 널값
        /// MapNode 반환
        /// </returns>
        public MapNode GetMapNode(int x, int y)
        {
            //인덱스가 음수가 나오면 NULL반환
            if (x < 0 || y < 0) return null;
            //Size 초과시 Null 반환
            else if (x >= MapSize.x || y >= MapSize.y) return null;
            else return MapData[(int)MapSize.y - y - 1][x];
        }
        /// <summary>
        /// 노드 특정 위치에 오브젝트 추가
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="KindObj">오브젝트</param>
        public void AddObj(int x, int y, int KindObj)
        {
            MapData[y][x].ObjSetting(KindObj); 
        }

    }
}
