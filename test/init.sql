-- 1. 创建并切换数据库
CREATE DATABASE IF NOT EXISTS chat;
USE chat;

-- 2. 创建 User 表
CREATE  TABLE User(
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(50) NOT NULL,
    state ENUM('online', 'offline') DEFAULT 'offline'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 3. 创建 Friend 表
CREATE TABLE Friend(
    userid INT NOT NULL,
    friendid INT NOT NULL,
    PRIMARY KEY (userid, friendid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 4. 创建 AllGroup 表
CREATE TABLE AllGroup(
    id INT PRIMARY KEY AUTO_INCREMENT,
    groupname VARCHAR(50) NOT NULL UNIQUE,
    groupdesc VARCHAR(200) DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 5. 创建 GroupUser 表
CREATE TABLE GroupUser(
    groupid INT NOT NULL,
    userid INT NOT NULL,
    grouprole ENUM('creator', 'normal') DEFAULT 'normal',
    PRIMARY key(groupid, userid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 6. 创建 offlineMessage 表
CREATE TABLE OfflineMessage(
    userid INT NOT NULL,
    message VARCHAR(500) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;