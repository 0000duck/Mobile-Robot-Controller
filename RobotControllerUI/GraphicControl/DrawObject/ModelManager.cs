using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX;
using System.Windows.Forms;
using Microsoft.DirectX.Direct3D;
using GraphicControl;
using System.Runtime.InteropServices;
using GraphicControl.Interface;

namespace GraphicControl.DrawObject
{
    /// <summary>
    /// Draw할 모델을 생성/관리 하는 팩토리 클래스
    /// </summary>
    public class ModelManager
    {
        protected List<ModelForDraw> DrawModelList;

        public const int ROBOT = 1;
        public const int HAZARD = 2;
        public const int COLOR = 3;

        private Device dev;
        /// <summary>
        /// 생성자
        /// </summary>
        public ModelManager(Device dev)
        {
            this.dev = dev;
            DrawModelList = new List<ModelForDraw>();
        }
        /// <summary>
        /// Create DrawModel
        /// </summary>
        public void CreateDrawModel(Device DXDevice , int Name , string TextureFileName)
        {
            ModelForDraw CreateModel = new ModelForDraw(DXDevice , Name);
            CreateModel.TextureLoad(TextureFileName);

            DrawModelList.Add(CreateModel);

        }
        /// <summary>
        /// 모델 (도형)을 로드만 하는 함수 (그리지 않음)
        /// </summary>
        /// <param name="Name">사용할 Model 이름</param>
        /// <returns>Find Sucess?</returns>
        private ModelForDraw LoadModel(int Name)
        {
            foreach (ModelForDraw model in DrawModelList)
            {
                if (model.ModelName == Name)
                {
                    
                    return model;
                }
            }

            return null;
        }
        public void Render(int Name )
        {
            ModelForDraw Loaded = LoadModel(Name);
            if (Loaded != null)
            {
                Loaded.Render();
                

            }
        }
        
    }
}
