#include "day07.h"

#include <memory>
#include <ranges>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

#include "../common/common.h"

namespace Advent::Day07 {

class FsDirectory;

class FsNode : public std::enable_shared_from_this<FsNode> {
public:
    FsNode() = delete;
    virtual ~FsNode() = default;

    void setParent(std::shared_ptr<FsDirectory> parent);
    virtual size_t size() const = 0;

protected:
    FsNode(std::string_view id)
        : m_id(id)
        , m_parent(std::weak_ptr<FsDirectory>()) {};

    std::weak_ptr<FsDirectory> m_parent;

private:
    std::string m_id;
};

class FsFile : public FsNode {
public:
    explicit FsFile(std::string_view id, size_t size = 0)
        : FsNode(id)
        , m_size(size)
    {
    }

    size_t size() const override { return m_size; }

private:
    size_t m_size;
};

class FsDirectory : public FsNode {
public:
    explicit FsDirectory(std::string_view id)
        : FsNode(id)
    {
    }

    void appendChild(std::shared_ptr<FsNode> node)
    {
        m_contents.push_back(node);
    }

    size_t size() const
    {
        size_t totalSize = 0;
        for (auto& node : m_contents) {
            totalSize += node->size();
        }
        return totalSize;
    }

private:
    std::vector<std::shared_ptr<FsNode>> m_contents;
};

void FsNode::setParent(std::shared_ptr<FsDirectory> parent)
{
    if (parent.get() != this) {
        parent->appendChild(shared_from_this());
        m_parent = parent;
    }
}

std::vector<std::shared_ptr<FsDirectory>> parseInput(std::string_view input)
{
    std::vector<std::shared_ptr<FsDirectory>> allDirs;

    std::vector<std::shared_ptr<FsDirectory>> dirStack;
    for (auto s : std::views::split(input, std::string_view {"\n"})) {
        std::string_view sv = std::string_view(s);

        auto getCmdArgs = [](std::string_view line, std::string_view cmd) {
            return line.substr(cmd.length() + 1);
        };

        std::string_view cdCmd = "$ cd";
        if (sv.starts_with(cdCmd)) {
            std::string_view cdArgs = getCmdArgs(sv, cdCmd);
            if (cdArgs == "..") {
                dirStack.pop_back();
            } else {
                auto newDir = std::make_shared<FsDirectory>(cdArgs);
                if (!dirStack.empty()) {
                    newDir->setParent(dirStack.back());
                }
                dirStack.push_back(newDir);
                allDirs.push_back(newDir);
            }
        } else if (isdigit(sv[0])) {
            size_t fileSize = ::atoi(sv.substr(0, sv.find(" ")).data());
            std::string_view fileName = sv.substr(sv.find(" ") + 1);

            auto newFile = std::make_shared<FsFile>(fileName, fileSize);
            newFile->setParent(dirStack.back());
        }
    }

    return allDirs;
}

int part1(const std::string& input)
{
    auto allDirs = parseInput(input);

    size_t sizeSum = 0;
    for (const auto& dir : allDirs) {
        size_t size = dir->size();
        if (size <= 100'000) {
            sizeSum += size;
        }
    }
    Advent::PrintLn("Size Sum: {}", sizeSum);

    return 0;
}

int part2(const std::string& input)
{
    auto allDirs = parseInput(input);

    size_t minDeletable = std::numeric_limits<size_t>::max();
    for (const auto& dir : allDirs) {
        size_t dirSize = dir->size();
        if (dirSize >= 358'913 && dirSize < minDeletable) {
            minDeletable = dirSize;
        }
    }
    Advent::PrintLn("Smallest Removable Directory: {}", minDeletable);

    return 0;
}

} // namespace Advent::Day07