#include <iostream>
#include <list>
#include <unordered_map>
#include <optional>

template <typename K, typename V>
class LRUCache {
    typedef std::pair<K, V> node_type;

    std::list<node_type> list;
    std::unordered_map<K, typename std::list<node_type>::iterator> map;
    int max_size;

public:
    explicit LRUCache(int n) : max_size(n) {}

    std::optional<V> get(K key) {
        if (map.find(key) == map.end())
            return std::nullopt;
        auto it = map[key];
        if (it != list.begin())
            list.splice(list.cbegin(), list, it, std::next(it));
        return (*it).second;
    }

    void put(K key, V value) {
        if (map.find(key) == map.end()) {
            if (list.size() == max_size) {
                map.erase(list.back().first);
                list.pop_back();
            }
            list.template emplace_front(std::make_pair(key, value));
            map[key] = list.begin();
        } else {
            auto it = map[key];
            if (it != list.begin())
                list.splice(list.cbegin(), list, it, std::next(it));
            (*it).second = value;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    LRUCache<int, int> cache(n);
    for (int i = 0; i < m; i++) {
        std::string s;
        std::cin >> s;
        if (s == "put") {
            int k, v;
            std::cin >> k >> v;
            cache.put(k, v);
        } else if (s == "get") {
            int k;
            std::cin >> k;
            auto res = cache.get(k);
            std::cout << (res.has_value() ? res.value() : -1) << std::endl;
        }
    }
}
