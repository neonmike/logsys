# 标准SOP - 日志模块开发与交付

## 适用范围与前置条件
- 适用：Linux/Ubuntu 环境下的 C 语言日志模块开发、测试与交付
- 前置：已安装 `git`、`gcc`、`make`；可访问 GitHub 并具有推送权限
- 项目路径：`/home/ubuntu/logsys`

## 流程总览（6A 工作流）
- Align：需求对齐 → 建立共识问题清单与边界
- Architect：系统分层设计 → 模块与接口契约
- Atomize：原子任务拆分 → 依赖图与验收标准
- Approve：人工审查 → 风险评估与可测性确认
- Automate：实现代码 → 编写测试 → 执行验证 → 文档同步
- Assess：结果评估 → 验收确认 → 生成总结与 TODO

## Align（对齐）
- 动作：
  - 阅读并更新 `说明文档.md` 的项目规划/进度模块
  - 创建并维护 `docs/日志模块/ALIGNMENT_日志模块.md`
  - 明确需求范围与边界，记录不确定点与决策清单
- 质量门控：需求边界清晰、技术约束明确、验收标准可测试

## Architect（架构）
- 动作：
  - 生成 `docs/日志模块/DESIGN_日志模块.md`（架构图、分层设计、接口契约、数据流与异常策略）
  - 复用现有组件和模式，避免过度设计
- 质量门控：与现有系统无冲突、接口定义完整、设计可行

## Atomize（原子化）
- 动作：
  - 生成 `docs/日志模块/TASK_日志模块.md`，拆分原子任务并定义输入/输出契约与验收标准
  - 生成任务依赖图（Mermaid）
- 质量门控：任务可独立验证、依赖清晰无循环、复杂度合理

## Approve（审批）
- 动作：
  - 按执行检查清单审查完整性/一致性/可行性/可控性/可测性
  - 通过后记录在 `docs/日志模块/CONSENSUS_日志模块.md`
- 质量门控：明确需求与验收、子任务定义、边界与限制、质量标准

## Automate（自动化执行）
- 动作：
  - 先写测试再写实现，持续运行验证
  - 执行构建与测试：
    - 构建：`make lib`
    - 测试：`make test`
    - 清理：`make clean`
  - 同步文档：在 `docs/日志模块/ACCEPTANCE_日志模块.md` 记录完成情况与验证结果
  - 代码要求：为所有函数添加函数级注释（功能、参数、返回值类型及用途）
- 质量门控：测试通过、功能完整、文档同步、无敏感信息泄露

## Assess（评估）
- 动作：
  - 更新 `docs/日志模块/ACCEPTANCE_日志模块.md` 并进行整体验收检查
  - 生成 `docs/日志模块/FINAL_日志模块.md`（总结报告）
  - 生成 `docs/日志模块/TODO_日志模块.md`（待办清单与缺少配置），并询问处理方式
- 质量门控：需求全部实现、验收标准满足、编译与测试通过、集成良好

## 版本控制与推送
- 初始化与提交：
  - `git init`
  - `git add .`
  - `git commit -m "feat: initial logging module and docs"`
  - `git branch -M main`
- 远程与推送：
  - 如遇所有权问题：`git config --global --add safe.directory /home/ubuntu/logsys`
  - 配置远程：`git remote add origin git@github.com:neonmike/logsys.git`
  - 推送：`git push -u origin main`
- 日常：`git pull`、`git push`、`git remote -v`

## 现有实现参考
- API 头文件：`include/logger.h:6-12,14-21,23-31`
- 核心实现与轮转：`src/logger.c:13-29,31-42,54-64,90-113`
- 构建脚本：`Makefile`
- 测试样例：`tests/test_logger.c:1-26`

## 测试策略
- 覆盖正常流程、边界条件与异常情况
- 日志级别过滤、控制台与文件输出、大小轮转与备份数量的验证
- 可考虑增加多线程场景、性能与压力测试（迭代项）

## 安全与合规
- 不提交密钥与敏感信息（使用 `.env` 管理，如后续需要）
- 文档与代码变更保持同步；提交信息清晰

## 建议的工程化增强（可选）
- 代码风格与静态检查：集成 `clang-format/clang-tidy` 与 `make lint`
- CI/CD：GitHub Actions 执行 `make lib && make test`
- 功能扩展：互斥锁保证线程安全、`syslog` 输出、彩色控制台、JSON/结构化日志