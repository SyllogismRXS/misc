from __future__ import print_function
import torch

# x = torch.empty(5, 3)
#
# x = torch.rand(5, 3)
#
# x = torch.zeros(5, 5, dtype=torch.long)
#
# x = torch.tensor([5, 3])
#
# x = x.new_ones(5, 3, dtype=torch.double)
#
# x = torch.randn_like(x, dtype=torch.float)
#
# y = x.numpy()
#
# print(x)
#
# if torch.cuda.is_available():
#     device = torch.device("cuda")          # a CUDA device object
#     y = torch.ones_like(x, device=device)  # directly create a tensor on GPU
#     x = x.to(device)                       # or just use strings ``.to("cuda")``
#     z = x + y
#     print(z)
#     print(z.to("cpu", torch.double))       # ``.to`` can also change dtype together!
# else:
#     print('No cuda')

##########

x = torch.ones(2, 2, requires_grad=True)


y = x + 2
z = y * y * 3
out = z.mean()

print(z, out)
