using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RobotControllerUI.AddOn.Map
{
    /// <summary>
    /// 맵의 한칸
    /// </summary>
    public class MapNode
    {
        public MapNode UpNode
        {
            get; protected set;
        }
        public MapNode DownNode
        {
            get; protected set;
        }
        public MapNode LeftNode
        {
            get;
            protected set;
        }
        public MapNode RightNode
        {
          get;
          protected set;
        }
        private int HavingObj;
        public MapNode() { }
        /// <summary>
        /// 네 방향의 Node를 받아 초기화하는 생성자
        /// </summary>
        /// <param name="Up"></param>
        /// <param name="Down"></param>
        /// <param name="Left"></param>
        /// <param name="Right"></param>
        public MapNode(MapNode Up, MapNode Down, MapNode Left, MapNode Right)
        {
            InitNearNode(Up , Down , Left , Right);
        }
        /// <summary>
        /// 주변노드 등록
        /// </summary>
        public void InitNearNode(MapNode Up, MapNode Down, MapNode Left, MapNode Right)
        {
            UpNode = Up; DownNode = Down; LeftNode = Left; RightNode = Right;
        }
        /// <summary>
        /// 가지고있는 오브젝트 종류 반환
        /// </summary>
        /// <returns></returns>
        public int WhatHave()
        {
            return HavingObj;
        }
        /// <summary>
        /// 가지고 있는 오브젝트 변경/설정
        /// </summary>
        /// <param name="ObjKind">바꿀 오브젝트 종류</param>
        public void ObjSetting(int ObjKind)
        {
            HavingObj = ObjKind;
        }
    }
}
