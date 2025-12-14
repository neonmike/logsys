# CONSENSUS - 日志模块

## 明确的需求与验收标准
- 功能：支持 `DEBUG/INFO/WARN/ERROR` 级别、控制台与文件输出、时间戳、本地/UTC时间、大小轮转（含备份）、级别阈值过滤。
- 验收：
  - 运行 `make test` 成功，控制台出现四级日志。
  - 生成 `build/test.log`，当大小超过阈值时产生 `build/test.log.1`、`build/test.log.2` 等备份。
  - 日志格式为 `YYYY-MM-DD HH:MM:SS [LEVEL] module: message`。

## 技术实现方案与约束
- C 语言实现，静态库输出；使用 GNU Make 构建。
- 不含线程安全；不含 syslog；不含彩色与结构化输出。

## 任务边界与集成方案
- 简单对外 API：`log_init/log_set_level/log_log/log_close` 与便捷宏。
- 集成方式：项目添加 `-Iinclude` 并链接 `build/liblogsys.a`。

## 不确定性解决
- 用户已授权按规则创建文档；后续扩展以新共识迭代。