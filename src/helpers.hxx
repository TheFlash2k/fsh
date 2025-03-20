#pragma once

#include <vector>
#include <algorithm>
#include <utility>

namespace List {

    template <typename _T=std::string>
    bool in_list(const std::vector<_T>& _vec, _T _data) {
        return std::find(_vec.begin(), _vec.end(), _data) != _vec.end();
    }

    template <typename _T=std::string>
    void remove_from_list(std::vector<_T>& _vec, _T elem) {
        _vec.erase(std::remove(_vec.begin(), _vec.end(), elem), _vec.end());
    }

    template <typename _T=std::string>
    _T get_next(const std::vector<_T>& _vec, _T elem) {
        auto it = std::find(_vec.begin(), _vec.end(), elem);
        if(it == _vec.end() || ++it == _vec.end())
            return nullptr;
        return *it;
    }

    template <typename _T=std::string>
    std::vector<_T> get_n_next(const std::vector<_T>& _vec, _T elem, size_t n=-1) {
        std::vector<_T> _n = {};
        if(n == -1) n = _vec.size();
        auto it = std::find(_vec.begin(), _vec.end(), elem);
        if(it == _vec.end())
            return _n;
        while(it != _vec.end() && n--) {
            _n.push_back(*it);
            ++it;
        }
        return _n;
    }

    template <typename _T>
    void stdout(const std::vector<_T>& _vec) {
        for(const auto& _v: _vec)
            std::cout << _v << std::endl;
    }
}

namespace String {

    void lstrip(std::string& _b) {
        _b.erase(_b.begin(), std::find_if(_b.begin(), _b.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    void rstrip(std::string& _b) {
        _b.erase(std::find_if(_b.rbegin(), _b.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), _b.end());
    }

    void strip(std::string& _b) {
        lstrip(_b);
        rstrip(_b);
    }

    void strip_all(std::vector<std::string>& buffer) {
        for(auto& _b: buffer)
            strip(_b);
    }

    void find_and_replace(std::string& text,
        const std::string& search, const std::string& replace) {
        size_t pos = 0;
        while ((pos = text.find(search, pos)) != std::string::npos) {
            text.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }
}