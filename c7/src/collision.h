#ifndef BAKUDAN_COLLISION_H_
#define BAKUDAN_COLLISION_H_

class Piece;

namespace collision
{

bool set_ms_at_collision_occur(const Piece& a, const Piece& b, unsigned* ms);

} // namespace collision

#endif
