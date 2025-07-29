![[GitBasicCommand.png]]

## 其他命令
```bash
git config --global user.name
git config --global user.email
git config --global --list
# system系统 global全局 local本地

git log --oneline # 只显示提交ID和提交信息

git diff # 工作区于 vs 暂存区
git diff HEAD # 工作区+暂存区 vs 本地仓库
git diff --cached/staged # 暂存区 vs 本地仓库
git diff HEAD~ HEAD # 比较提交之间的差异

git rm -r * # 递归删除当前目录下所有文件

git status -s # 简洁地显示状态

git submodule add <repository> <path>
git submodule update 
git clone <repository> --recursive # 递归地克隆项目
```

## .gitignore文件
```bash
/*.a   # 忽略当前目录下所有.a文件
*.a    # 忽略当前及子目录下所有的.a文件
!lib.a # 在忽略对象中排除lib.a文件
/TODO  # 只忽略当前目录下的TODO文件，不包含子目录中的其他同名文件
build/ # 忽略build文件夹
doc/*.txt    # 忽略doc目录下所有.pdf文件
doc/**/*.pdf # 忽略doc目录及子目录下所有.pdf文件
```

## SSH配置
进入~/.ssh目录并输入以下命令
```bash
ssh-keygen -t rsa -b 4096 -c "example@exaple.com" # 生成rsa类型密钥，长度为4096并附带注释
```
生成以下两个文件
```bash
id_rsa.pub # 公钥 
id_rsa     # 私钥
```
将私钥内容复制到GitHub完成配置

## 关联本地仓库和远程仓库
```bash
git init # 初始化本地仓库

git remote add origin https://github.com/MyUser/RepoName.git # 添加远程仓库
git branch -M main # 指定本地分支名称
git push -u origin main:main # 关联远程main分支和本地main分支
```

## Fork 和 Pull Request
### 给他人仓库贡献代码
点击Fork按钮复制仓库到自己的账户下
```bash
git clone https://github.com/MyUser/RepoName.git # 克隆仓库到本地
```
进入仓库目录
```bash
git checkout -b <LocalBranchName> # 创建新分支
```
修改代码后
```bash
git push origin <LocalBranchName> # 推送给远程分支
```
推送后的所有修改都只在自己的远程仓库，若想要提交给原作者（原始仓库/上游仓库）
需要在 Github 上创建 Pull Request 提交申请

### 当原始仓库更改时需要及时同步
```bash
git remote add upstream https://github.com/OriginUser/OriginRepo.git # 添加上游仓库
git fetch upstream # 获取上游仓库最新代码
git checkout main  # 切换到需要合并的本地分支
git merge upstream/main # 把上游main分支的代码合并到本地分支
```
记得要处理冲突

## fetch 和 pull 的区别
```bash
git fetch origin # 获取远程仓库最新信息
git merge origin/main # 合并到当前分支

git pull origin main # 以上两个命令的组合，隐藏中间过程，不推荐使用
```