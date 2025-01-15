
        var channel;    
        var qtObject;

        // 初始化 WebChannel
        function init() {
            if (!qt || !qt.webChannelTransport) {
                console.error("Qt WebChannel 未正确加载！");
                return;
            }

            new QWebChannel(qt.webChannelTransport, function (newChannel) {
                channel = newChannel;
                qtObject = channel.objects.QtObject; // QtObject 在 Qt 中已注册

                // 监听来自 Qt 的信号
                if (qtObject && qtObject.sendToHtml) {
                    qtObject.sendToHtml.connect(function(response) {
                        updateContent(response);
                    });
                } else {
                    console.warn("未检测到 QtObject 或 sendToHtml 信号");
                }
            });
        }

        // 更新页面内容
        function updateContent(content) {
            const contentDisplay = document.getElementById("contentDisplay");
            contentDisplay.innerText = content;
        }

        // 按钮事件绑定
        window.onload = function () {
            init();

            const buttonIp = document.getElementById("ipconfig");
            const buttonDir = document.getElementById("dir");
            const buttonStart = document.getElementById("start");
            const buttonPing = document.getElementById("ping");
           
            // ipconfig 
            buttonIp.addEventListener('click', () => {
                if (qtObject) {
                    qtObject.updateContent("ipconfig");
                } else {
                    console.error("qtObject 未初始化");
                }
            });

            // dir 
            buttonDir.addEventListener('click', () => {
                const dirInput = document.getElementById("dirInput").value.trim().replace(/^"|"$/g,"");
                if (qtObject) {
                    qtObject.updateContent("dir"+" "+dirInput);
                } else {
                    console.error("qtObject 未初始化");
                }
            });
            //start
            buttonStart.addEventListener('click', () => {
                const dirInput = document.getElementById("dirInput").value.trim().replace(/^"|"$/g,"");
                if (qtObject) {
                    qtObject.updateContent("start"+" "+dirInput);
                } else {
                    console.error("qtObject 未初始化");
                }
            });
            //ping
            buttonPing.addEventListener('click', function()  {
                window.location.href = "ping/ping.html";
            });
        };