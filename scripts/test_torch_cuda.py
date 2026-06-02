import torch
print(f"CUDA available: {torch.cuda.is_available()}")
if torch.cuda.is_available():
    print(f"Graphicscard detected: {torch.cuda.get_device_name(0)}")