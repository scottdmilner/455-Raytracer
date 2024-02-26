//
// Created by Scott Milner on 2/21/24.
//

#ifndef RAY_TRACER_DUAL_STREAM_H
#define RAY_TRACER_DUAL_STREAM_H
#include <ostream>


class dual_stream {
public:
    dual_stream (std::ostream& os1, std::ostream& os2): os1(os1), os2(os2) {}

    template<class T> dual_stream& operator<<(const T& x) {
        os1 << x;
        os2 << x;
        return *this;
    }
private:
    std::ostream& os1;
    std::ostream& os2;
};


#endif //RAY_TRACER_DUAL_STREAM_H
