#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <fstream>

#include <vector>

#include <string>

#include <sstream>

#include <algorithm>

#include <ctime>

using namespace std;
// 抽象基类：用户信息接口

class UserInfo {

public:

// 虚析构函数

virtual ~UserInfo () {};
// 纯虚函数：显示个人信息

virtual void showPersonalInfo () const = 0;

// 纯虚函数：更新个人信息

//infoType: 1 - 用户名 2 - 所在地 3 - 个性签名

virtual bool updateInfo (int infoType, const string& newValue) = 0;
};
// ===================== 用户类（公有继承 UserInfo 基类） =====================

class User : public UserInfo

{

private:

int userId;                 // 个人 ID

string account;             // 账号

string location;            // 所在地

string signature;           // 个性签名

vector<int> friendList;     // 好友 ID 列表

vector<int> blackList;      // 黑名单 ID 列表

string password;            // 用户密码

string Name;                // 用户名
public:

// 构造函数：初始化 ID 和账号，其余默认值

User (int id, const string& acc, const string& pwd, const string& name)

: userId (id), account (acc), location ("未设置"), signature ("暂无签名"),

password (pwd), Name (name)

{}
// 获取

int getUserId () const { return userId;}

string getAccount () const { return account; }

string getLocation () const { return location; }

string getSignature () const { return signature; }

const vector<int>& getFriendList() const { return friendList; }

const vector<int>& getBlackList() const { return blackList; }

string getName() const { return Name; }

string getPassword() const { return password; }</int></int>

void setLocation (const string& loc) { location = loc; }

void setSignature (const string& sig) { signature = sig; }

void setName (const string& name) { Name = name; } // 新增：用户名修改接口

// 虚函数重写

void showPersonalInfo () const override

{

cout << "==================== 个人信息 ====================" << endl;

cout << "用户 ID：\t" << userId << endl;

cout << "登录账号：\t" << account << endl;

cout << "用户名：\t" << Name << endl;

cout << "所在地：\t" << location << endl;

cout << "个性签名：\t" << signature << endl;

cout <<"好友数量：\t" << friendList.size () << endl;

cout << "黑名单数量：\t" << blackList.size () << endl;

cout << "==================================================" << endl;

}

bool updateInfo(int infoType, const string& newValue) override

{

switch (infoType)

{

case 1: Name = newValue;      return true;

case 2: location = newValue;  return true;

case 3: signature = newValue; return true;

default: return false;

}

}

// 好友操作

void addFriend (int friendId)

{

// 已经是好友 / 加自己 都直接跳过

if (friendId == userId || isFriend (friendId))

return;

friendList.push_back (friendId);

}

void deleteFriend(int friendId)

{

auto it = find(friendList.begin(), friendList.end(), friendId);

if (it != friendList.end())

friendList.erase(it);

}

bool isFriend(int friendId) const

{

return find(friendList.begin(), friendList.end(), friendId) != friendList.end();

}

// 黑名单操作

void addBlack (int targetId)

{

if (targetId == userId || isBlack (targetId))

return;

blackList.push_back (targetId);

}

void removeBlack(int targetId)

{

auto it = find(blackList.begin(), blackList.end(), targetId);

if (it != blackList.end())

blackList.erase(it);

}

bool isBlack(int targetId) const

{

return find(blackList.begin(), blackList.end(), targetId) != blackList.end();

}

bool checkPassword(const string& pwd) const

{

return password == pwd;

}

//  运算符重载

bool operator==(const string& targetAccount) const

{

return account == targetAccount;

}

bool operator==(const User& other) const

{

return userId == other.userId;

}
};
// 支持 账号字符串 == 用户 不写，用 “aaaaa”=user 报错

bool operator==(const string& targetAccount, const User& user)

{

return user == targetAccount;

}
// ===================== 系统管理类 =====================

class SocialManager

{

private:

vector<User> allUsers;

vector<string> allChatLines;

vector<string> allMomentLines;

int nextUserId = 1;
const string userFile = "users.txt";

const string chatFile = "chats.txt";

const string momentFile = "moments.txt";

string getCurrentTime () const// 得到时间的工具

{

time_t now = time (0);//timet 得到时间戳，是一个秒数

char buf [80];// 用来放时间

strftime (buf, sizeof (buf), "% Y-% m-% d % H:% M", localtime (&now));

return buf;

}

// 工具：逗号分隔字符串转 int 数组

vector<int> reInt(const string& s, char sep) const

{

vector<int> res;

stringstream a(s);

string item;

while (getline(a, item, sep))

{

if (!item.empty())

res.push_back(stoi(item));

}

return res;

}</int></int>

// 工具：int 数组转逗号分隔字符串

string goInt (const vector<int>& vec, char sep) const

{

string res;

for (size_t i = 0; i < vec.size(); i++)

{

if (i > 0) res += sep;

res += to_string(vec[i]);

}

return res;

}
public:

void loadAllData()

{

loadUsers();

loadChats();

loadMoments();

}
void saveAllData()

{

saveUsers();

saveChats();

saveMoments();

}

// 注册新用户（ID 由系统分配，保证唯一）

bool registerUser (const string& account, const string& password, const string& name)

{

if (findUserByAccount (account) != nullptr)

return false;

if (findUserByName (name) != nullptr)

return false;

allUsers.emplace_back (nextUserId++, account, password, name);

return true;

}

// 删除用户（注销账号）

bool deleteUser (int uid)

{

auto it = find_if (allUsers.begin (), allUsers.end (), [uid](const User& u) {

return u.getUserId () == uid;

});

if (it == allUsers.end ())

return false;

// 同步清理所有用户的好友列表和黑名单中的该用户

for (auto& u : allUsers)

{

u.deleteFriend (uid);

u.removeBlack (uid);

}

allUsers.erase(it);

return true;

}

// 按 ID 查找用户

User* findUserById (int uid)

{

for (auto& u : allUsers)

{

if (u.getUserId () == uid)

return &u;

}

return nullptr;

}

// 按 name 查找用户

User* findUserByName (const string& name)

{

for (auto& u : allUsers)

{

if (u.getName () == name)

return &u;

}

return nullptr;

}

// 按账号查找用户

User* findUserByAccount (const string& account)

{

for (auto& u : allUsers)

{

if (u == account)

return &u;

}

return nullptr;

}

// 按账号加好友

bool addFriendByAccount (int myId, const string& targetAccount)

{

User* me = findUserById (myId);

User* target = findUserByAccount (targetAccount);

if (!me || !target) return false;

if (me->getUserId () == target->getUserId ()) return false;

if (me->isBlack (target->getUserId ()) || target->isBlack (me->getUserId ()))

return false;

if (me->isFriend (target->getUserId ())) return false;

me->addFriend(target->getUserId());

target->addFriend(me->getUserId());

return true;

}

// 拉黑用户（拉黑后自动删除双方好友）

bool blackUser (int myId, int targetId)

{

User* me = findUserById (myId);

User* target = findUserById (targetId);

if (!me || !target) return false;

me->addBlack(targetId);

me->deleteFriend(targetId);

target->deleteFriend(myId);

return true;

}

// 解除拉黑

bool unblackUser (int myId, int targetId)

{

User* me = findUserById (myId);

User* target = findUserById (targetId);

if (!me || !target) return false;

if (!me->isBlack (targetId)) return false;

me->removeBlack(targetId);

return true;

}

// 发送消息

bool sendChat (int myId, int targetId, const string& content)

{

if (!findUserById (myId) || !findUserById (targetId))

return false;

string line = to_string (myId) + "|" + to_string (targetId) + "|" + content + "|" + getCurrentTime ();

allChatLines.push_back (line);

return true;

}

// 获取和指定好友的双向聊天记录

vector<string> getChatWithFriend(int myId, int friendId) const

{

vector<string> res;

for (const string& line : allChatLines)

{

stringstream ss(line);

string fromStr, toStr;

getline(ss, fromStr, '|');

getline(ss, toStr, '|');</string></string>

int fromId = stoi(fromStr);

int toId = stoi(toStr);

if ((fromId == myId && toId == friendId) || (fromId == friendId && toId == myId))

res.push_back(line);

}

return res;

}

// 发布动态

bool publishMoment (int userId, const string& content)

{

if (!findUserById (userId)) return false;

string line = to_string (userId) + "|" + content + "|" + getCurrentTime () + "|";

allMomentLines.push_back (line);

return true;

}

// 获取所有动态（带用户名 + 账号）

vector<string> getAllMoments() const

{

vector<string> res;

for (const string& line : allMomentLines)

{

stringstream ss(line);

string uidStr, content, timeStr;

getline(ss, uidStr, '|');

getline(ss, content, '|');

getline(ss, timeStr, '|');

int uid = stoi(uidStr);</string></string>

string userName = "未知用户";

string userAccount = "0000";

for (const auto& u : allUsers)

{

if (u.getUserId () == uid)

{

userName = u.getName ();

userAccount = u.getAccount ();

break;

}

}

string formatLine = "【" + userName + "（账号：" + userAccount + "）】" + timeStr + "\n" + content;

res.push_back (formatLine);

}

return res;

}
private:

// 文件读写

void loadUsers ()

{

ifstream in (userFile);

if (!in) return;
string line;

while (getline (in, line))

{

if (line.empty ()) continue;// 跳过空行

stringstream ss (line);

vector<string> cols;

string item;

while (getline (ss, item, '|'))

cols.push_back (item);

if (cols.size () < 8) continue;// 确保有 8 个 |</string>

int id = stoi(cols[0]);

User u(id, cols[1], cols[2], cols[3]);

u.setLocation(cols[4]);

u.setSignature(cols[5]);

vector<int> friends = reInt(cols[6], ',');

for (int fid : friends) u.addFriend(fid);

vector<int> blacks = reInt(cols[7], ',');

for (int bid : blacks) u.addBlack(bid);</int></int>

allUsers.push_back(u);

if (id >= nextUserId) nextUserId = id + 1;

}

in.close();

}

void saveUsers()

{

ofstream out(userFile);

for (auto& u : allUsers)

{

out << u.getUserId() << "|"

<< u.getAccount() << "|"

<< u.getPassword() << "|"

<< u.getName() << "|"

<< u.getLocation() << "|"

<< u.getSignature() << "|"

<< goInt(u.getFriendList(), ',') << "|"

<< goInt(u.getBlackList(), ',') << "|" << endl;

}

out.close();

}

void loadChats()

{

ifstream in(chatFile);

if (!in) return;

string line;

while (getline(in, line))

if (!line.empty()) allChatLines.push_back(line);

in.close();

}

void saveChats()

{

ofstream out(chatFile);

for (const string& line : allChatLines)

out << line << endl;

out.close();

}

void loadMoments()

{

ifstream in(momentFile);

if (!in) return;

string line;

while (getline(in, line))

if (!line.empty()) allMomentLines.push_back(line);

in.close();

}

void saveMoments()

{

ofstream out(momentFile);

for (const string& line : allMomentLines)

out << line << endl;

out.close();

}
};
// 登录注册菜单，返回登录成功的用户 ID，失败返回 - 1

int loginMenu (SocialManager& manager)

{

string account, password;

cout << "请输入账号:";

getline (cin, account);

cout << "请输入密码:";

getline (cin, password);
User* user = manager.findUserByAccount (account);

if (!user || !user->checkPassword (password))

{

cout << "账号或密码错误！" << endl;

return -1;

}

cout << "登录成功，欢迎" << user->getName () << "！" << endl;

return user->getUserId ();
}
// 注册功能

void registerMenu (SocialManager& manager)

{

string account, password, name;

cout << "请输入账号:";

getline (cin, account);

cout << "请输入密码:";

getline (cin, password);

cout << "请输入用户名:";

getline (cin, name);
if (manager.registerUser (account, password, name))

cout << "注册成功！请登录使用" << endl;

else

cout << "注册失败，账号或用户名已存在" << endl;
}
// 聊天模块

void chatModule (SocialManager& manager, int currentUserId)

{

User* me = manager.findUserById (currentUserId);

if (!me) return;

const vector<int>& friendIds = me->getFriendList();
if (friendIds.empty ())

{

cout << "你还没有好友，快去联系人中添加吧！" << endl;

return;

}

cout << "\n===== 好友列表 =====\n";

vector<int> validIds;

for (size_t i = 0; i < friendIds.size(); i++)

{

User* u = manager.findUserById(friendIds[i]);

if (u)

{

validIds.push_back(u->getUserId());

cout << i + 1 << ". " << u->getName() << endl;

}

}</int>

cout <<"请选择好友序号进入聊天 (0 返回):";

int idx;

cin >> idx;

cin.ignore ();

if (idx == 0 || idx < 1 || idx > validIds.size ()) return;

int targetId = validIds[idx - 1];

User* target = manager.findUserById(targetId);

if (!target) return;

while (true)

{

cout << "\n===== 与" << target->getName () << "的聊天 =====\n";

vector<string> chats = manager.getChatWithFriend (currentUserId, targetId);

if (chats.empty ())

{

cout << "暂无聊天记录 \n";

}

else

{

for (const string& line : chats)

{

stringstream ss (line);

string fromStr, toStr, content, timeStr;

getline (ss, fromStr, '|');

getline (ss, toStr, '|');

getline (ss, content, '|');

getline (ss, timeStr, '|');</string>

int fromId = stoi (fromStr);

User* sender = manager.findUserById (fromId);

string senderName = sender ? sender->getName () : "未知用户";

cout << "[" << timeStr << "]" << senderName << ":" << content << endl;

}

}

cout << "\n------------------------\n";

cout <<"对方昵称:" << target->getName () << endl;

cout << "个性签名:" << target->getSignature () << endl;

cout << "所在地:" << target->getLocation () << endl;

cout << "------------------------\n";

cout << "1. 发送消息 \n0. 退出聊天 \n 请选择:";

int op;

cin >> op;

cin.ignore ();

if (op == 0) break;

if (op == 1)

{

string content;

cout << "请输入消息内容:";

getline (cin, content);

cout << (manager.sendChat (currentUserId, targetId, content) ? "发送成功！" : "发送失败！") << endl;

}

}
}
// 联系人模块

void contactModule (SocialManager& manager, int currentUserId)

{

while (true)

{

cout << "\n===== 联系人 =====\n1. 好友列表 \n2. 黑名单 \n0. 返回 \n 请选择:";

int choice;

cin >> choice;

cin.ignore ();

if (choice == 0) break;
User* me = manager.findUserById(currentUserId);

if (!me) continue;

if (choice == 1)

{

// 好友列表管理

cout << "\n===== 我的好友 =====\n";

const vector<int>& friendIds = me->getFriendList ();

if (friendIds.empty ())

cout << "暂无好友 \n";

else

for (int fid : friendIds)

if (User* u = manager.findUserById (fid))

cout << "-" << u->getName () << endl;</int>

cout << "\n1. 添加好友 \n2. 删除好友 \n0. 返回 \n 请选择:";

int op;

cin >> op;

cin.ignore ();

if (op == 0) continue;

string acc;

cout << "请输入对方账号:";

getline (cin, acc);

if (op == 1)

{

bool ok = manager.addFriendByAccount (currentUserId, acc);

cout << (ok ? "添加好友成功！" : "添加失败（账号不存在 / 已拉黑 / 已是好友）") << endl;

}

else if (op == 2)

{

User* target = manager.findUserByAccount (acc);

if (!target || !me->isFriend (target->getUserId ()))

{

cout << "删除失败，账号不在好友列表中" << endl;

}

else

{

me->deleteFriend (target->getUserId ());

target->deleteFriend (me->getUserId ());

cout << "删除好友成功！" << endl;

}

}

}

else if (choice == 2)

{

// 黑名单管理

cout << "\n===== 我的黑名单 =====\n";

const vector<int>& blackIds = me->getBlackList ();

if (blackIds.empty ())

cout << "黑名单为空 \n";

else

for (int bid : blackIds)

if (User* u = manager.findUserById (bid))

cout << "-" << u->getName () << endl;</int>

cout << "\n1. 加入黑名单 \n2. 移出黑名单 \n0. 返回 \n 请选择:";

int op;

cin >> op;

cin.ignore ();

if (op == 0) continue;

string acc;

cout << "请输入对方账号:";

getline (cin, acc);

User* target = manager.findUserByAccount (acc);

if (!target)

{

cout << "操作失败，账号不存在" << endl;

}

else if (op == 1)

{

if (target->getUserId () == currentUserId)

{

cout << "不能拉黑自己" << endl;

}

else

{

manager.blackUser (currentUserId, target->getUserId ());

cout << "已加入黑名单，双方好友关系已解除" << endl;

}

}

else if (op == 2)

{

bool ok = manager.unblackUser (currentUserId, target->getUserId ());

cout << (ok ? "已移出黑名单" : "操作失败，账号不在黑名单中") << endl;

}

}

}
}
// 动态模块

void momentModule (SocialManager& manager, int currentUserId)

{

while (true)

{

cout << "\n===== 全部动态 =====\n";

vector<string> moments = manager.getAllMoments ();

if (moments.empty ())

cout << "还没有人发布动态 \n";

else

for (const string& m : moments)

cout << m << endl << endl;
cout << "1. 发布动态 \n0. 返回 \n 请选择:";

int op;

cin >> op;

cin.ignore ();

if (op == 0) break;

if (op == 1)

{

string content;

cout << "请输入动态内容:";

getline (cin, content);

cout << (manager.publishMoment (currentUserId, content) ? "发布成功！" : "发布失败！") << endl;

}

}
}
// 新增：个人信息模块

void profileModule (SocialManager& manager, int& currentUserId)

{

User* me = manager.findUserById (currentUserId);

if (!me) return;
while (true)

{

cout << "\n===== 个人信息 =====\n1. 查看个人信息 \n2. 修改个人信息 \n3. 注销账号 \n0. 返回 \n 请选择:";

int choice;

cin >> choice;

cin.ignore ();

if (choice == 0) break;

if (choice == 1)

{

// 基类指针调用虚函数，体现多态特性

UserInfo* infoPtr = me;

infoPtr->showPersonalInfo ();

}

else if (choice == 2)

{

while (true)

{

cout << "\n===== 修改个人信息 =====\n1. 修改用户名 \n2. 修改所在地 \n3. 修改个性签名 \n0. 返回 \n 请选择:";

int op;

cin >> op;

cin.ignore ();

if (op == 0) break;

if (op < 1 || op> 3)

{

cout << "无效选项，请重新输入！" << endl;

continue;

}

string newValue;

cout << "请输入新内容:";

getline (cin, newValue);

if (newValue.empty ())

{

cout << "内容不能为空！" << endl;

continue;

}

// 用户名修改需校验重名

if (op == 1)

{

User* existUser = manager.findUserByName (newValue);

if (existUser && existUser->getUserId () != currentUserId)

{

cout << "修改失败，该用户名已被占用！" << endl;

continue;

}

}

bool res = me->updateInfo (op, newValue);

cout << (res ? "修改成功！" : "修改失败！") << endl;

}

}

else if (choice == 3)

{

cout << "！！！  注销后所有数据将永久删除且无法恢复，确定注销吗？(输入 Y 确认，其他取消):";

char confirm;

cin >> confirm;

cin.ignore ();

if (confirm == 'Y' || confirm == 'y')

{

if (manager.deleteUser (currentUserId))

{

manager.saveAllData ();

cout << "账号已注销，数据已清除。" << endl;

currentUserId = -1; // 标记为未登录，退回主菜单

return;

}

else

{

cout << "注销失败，用户不存在。" << endl;

}

}

else

{

cout << "已取消注销操作。" << endl;

}

}

else

{

cout << "无效选项，请重新输入！" << endl;

}

}
}
// ===================== 主函数（总控入口，非常精简） =====================

int main ()

{
SocialManager manager;

manager.loadAllData();

int currentUserId = -1;

while (true)

{

cout << "\n===== 社交系统 =====\n1. 登录 \n2. 注册 \n0. 退出系统 \n 请选择:";

int choice;

cin >> choice;

cin.ignore ();

if (choice == 0)

{

manager.saveAllData ();

cout << "数据已保存，欢迎下次使用！" << endl;

break;

}

else if (choice == 1)

{

currentUserId = loginMenu (manager);

if (currentUserId == -1) continue;

// 登录后功能主菜单

while (true)

{

cout << "\n===== 功能菜单 =====\n1. 消息 \n2. 联系人 \n3. 动态 \n4. 个人信息 \n0. 退出登录 \n 请选择:";

int mainChoice;

cin >> mainChoice;

cin.ignore ();

if (mainChoice == 0)

{

manager.saveAllData ();

cout << "已退出登录，数据已保存。" << endl;

currentUserId = -1;

break;

}

else if (mainChoice == 1) chatModule (manager, currentUserId);

else if (mainChoice == 2) contactModule (manager, currentUserId);

else if (mainChoice == 3) momentModule (manager, currentUserId);

else if (mainChoice == 4) profileModule (manager, currentUserId);

else cout << "无效选项，请重新输入！" << endl;

// 注销后自动退出到登录界面

if (currentUserId == -1) break;

}

}

else if (choice == 2)

{

registerMenu (manager);

}

else

{

cout << "无效选项，请重新输入！" << endl;

}

}

return 0;
} 