# Vanilla-Base-2016
萌谷王《OpenGL入门Window版》（2016）学习笔记

## Win32应用添加控制台调试
`右键项目属性 -> 配置属性 -> 生成事件 -> 后期生成事件 -> 命令行` 添加如下内容：


> editbin /subsystem:console $(OutDir)$(ProjectName).exe
