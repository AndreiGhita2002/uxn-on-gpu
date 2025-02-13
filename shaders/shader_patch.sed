s/ArrayStride 16/ArrayStride 4/g
# ram offset:
s/OpMemberDecorate %UXN_Buffer 1 Offset 16/OpMemberDecorate %UXN_Buffer 1 Offset 4/g
# wst:
s/OpMemberDecorate %UXN_Buffer 2 Offset 1048592/OpMemberDecorate %UXN_Buffer 2 Offset 262148/g
# wst pointer:
s/OpMemberDecorate %UXN_Buffer 3 Offset 1052688/OpMemberDecorate %UXN_Buffer 3 Offset 263172/g
# rst:
s/OpMemberDecorate %UXN_Buffer 4 Offset 1052704/OpMemberDecorate %UXN_Buffer 4 Offset 263176/g
# rst pointer:
s/OpMemberDecorate %UXN_Buffer 5 Offset 1056800/OpMemberDecorate %UXN_Buffer 5 Offset 264200/g
# dev:
s/OpMemberDecorate %UXN_Buffer 6 Offset 1056816/OpMemberDecorate %UXN_Buffer 6 Offset 264204/g
# flag:
s/OpMemberDecorate %UXN_Buffer 7 Offset 1060912/OpMemberDecorate %UXN_Buffer 7 Offset 265228/g
