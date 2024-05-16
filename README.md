## 功能为，画笔，文字，马赛克，撤回，清除，ocr（基于百度的api），选取之后双击可以直接粘贴到剪贴板
imgocrclient是实现ocr的类，需要自己去百度注册账号，个人注册会很快，m_clientId = "";m_clientSecret = "";这两个参数需要自己在构造函数初始化填写注册之后获取的id和key。
infolabel是遮罩
pinchartwindow是钉图功能
screenshot，没啥用，只是用来打开个窗口点击个按钮的
screenshotwidget，这个类是主要的截屏类，初始化之后就开始到了截屏的时候
tool_bar是截图之后出现的工具栏，主要功能都在这个，功能的实现卸载了screenshotwidget里
