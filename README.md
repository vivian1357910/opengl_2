# opengl_2
俄羅斯方塊

作業環境：Windows10 64bit

編輯器：Visual Studio 2019

語言：C++

套件：OpenGL、Freeglut(引用自NuGet nupengl.core)




作業要求：

1.建立一個Tetris遊戲的視窗，需要包含四個要素：

	a.Game board：遊戲的主要窗口，大小為20*20，可容納200個方塊。
  
	b.Preview window：在左上角預覽窗口顯示下一個將生成的方塊。
  
	c.Score display：顯示當前累積分數。消除一排方塊獲得10分，若同時消除越多排分數越高。
  
		(計算公式：score += 10 * 一次消除排數的平方)
    
	d.Level display：指當前難度，控制方塊的下落速度。分數每增加20分，上升難度，加快下落速度。最高到 Level 6
  

2.將四格骨牌設計出來，依照遊戲的規則：

	-設計出七種四格骨牌，如投影片第8頁的展示
  
	-旋轉時，以設為中心的方塊為基準
  
	-遊戲開始時，從Game board最上方中間的位置落下
  
	-當方塊下落到Game board最下方，或落到其他方塊上，無法再向下移動時，會固定在該處，換下一個新的隨機方塊落下
  
	-某一橫行的格子全部由方塊填滿時，會被消除並成為玩家的得分
  
	-當四格骨牌固定時，碰到Game board最上排的位置，遊戲會結束
  


3.遊戲功能的鍵盤按鈕配置：

	-左Shift：開始遊戲
  
	-右Shift：結束遊戲
  
	-下：方塊加速往下
  
	-左：方塊左移(單位一格)
  
	-右：方塊右移(單位一格)
  
	-左Ctrl：方塊逆時針旋轉
  
	-左Alt：方塊順時針旋轉
  
  


4.視窗開啟後，按開始鍵(左Shift)即可直接開始遊戲，遊戲結束後要有Game over的提示。



bonus：

1.Game over畫面為已落下的方塊轉為灰色，並在中央顯示Game over字樣，五秒後自動關閉視窗。
