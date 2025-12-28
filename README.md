# 贪吃蛇游戏
基于C语言和EasyX图形库开发的贪吃蛇游戏。

## 控制方式
方向控制: W/A/S/D 或 方向键
空格键: 暂停/继续
R键: 重新开始

## 游戏特色
动态难度（速度随分数增加）
粒子特效和屏幕抖动
自动保存最高分
背景音乐和音效

## 文件
Bscore.txt: 保存历史最高分
三个.wav文件: 游戏音效

## 功能模块

### 数据结构
Body: 蛇身节点，包含位置和方向
Snake: 蛇对象，管理整个蛇身
Food: 食物对象，包含位置和激活状态
Particle: 粒子效果，用于食物被吃时的特效

### 主要函数
printSnake(): 渲染蛇身
printfFood(): 渲染食物
moveSnake(): 处理蛇的移动
createFood(): 生成新食物
updateScore(): 更新最高分记录
resetGame(): 重置游戏状态

## 引用
背景音乐：https://www.bilibili.com/video/BV1xs4y1w7DD
吃/死亡音效：https://pixabay.com/zh/sound-effects

## AI指导
ChatGPT-5：历史最高分数记录 食物粒子特效 音乐播放
DeepSeek：整体Bug检查 按键触发问题、音乐播放无声音等Bug
