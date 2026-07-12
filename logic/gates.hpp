#ifndef TRIOS_GATES_HPP
#define TRIOS_GATES_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "trit.hpp"

namespace trios {

// class Gate {
// public:
//     Gate() = default;
//     virtual ~Gate() = default;

//     virtual bool evaluate() const = 0;
//     virtual std::string name() const = 0;
// };

class AndGate {
public:
    Trit evaluate(const std::vector<Trit>& inputs) const;
};

class OrGate {
public:
    Trit evaluate(const std::vector<Trit>& inputs) const;
};

class NotGate {
public:
    Trit evaluate(const Trit& input) const;
};

// class OrGate : public Gate {
// public:
//     explicit OrGate(std::vector<bool> inputs);
//     bool evaluate() const override;
//     std::string name() const override;

// private:
//     std::vector<bool> m_inputs;
// };

// class NotGate : public Gate {
// public:
//     explicit NotGate(bool input);
//     bool evaluate() const override;
//     std::string name() const override;

// private:
//     bool m_input;
// };

} // namespace trios

#endif // TRIOS_GATES_HPP
