#pragma once

class endOfFile : public std::exception {
private:
    std::string s;
public:
    endOfFile() : s{std::string{"End of file"}} {};

    const char * what() const override {
        return s.c_str();
    };
};

class invalidPosition : public std::exception {
private:
    std::string s;
public:
    invalidPosition(const char& c) : s{std::string{"Invalid position: "} + c} {};

    const char * what() const override {
        return s.c_str();
    };
};

class invalidValue : public std::exception {
private:
    std::string s;
public:
    invalidValue(std::string valueName, const char& value) : s{std::string{"Invalid value for "} + valueName + "(" + value +")"} {};

    const char * what() const override {
        return s.c_str();
    };
};

class unknownColor : public std::exception {
private:
    std::string s;
public:
    unknownColor(std::string s) : s{std::string{"Unknown color: "} + s} {};

    const char* what() const override {
        return s.c_str();
    }
};

class unknownShape : public std::exception {
private:
    std::string s;
public:
    unknownShape(std::string s) : s{std::string{"Unknown shape: "} + s} {};

    const char* what() const override {
        return s.c_str();
    }
};