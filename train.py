import torch # type: ignore
import torch.nn as nn #type: ignore
import torch.nn.functional as F #type: ignore

class HanabiAgent(nn.Module):
    def __init__(self, input_size = 128, hidden_size = 256, action_space_size = 100):
        super().__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, action_space_size)
    
    def forward(self, x):
        x = F.relu(self.fc1(x))
        return self.fc2(x)
    
def encode_state(state_string):
    return torch.randn(1, 128)

agent = HanabiAgent()
state_string = "test_string"
encoded_state = encode_state(state_string)
