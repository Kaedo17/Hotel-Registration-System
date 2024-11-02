 while (getline(authenticator, fileUserName) && getline(authenticator, filePasswd)) {
        //cout << fileUserName << " " << filePasswd;
        if (fileUserName == staffUserName && filePasswd == staffPasswd) {
            userAuthenticated = true;
            break;
        }
    }