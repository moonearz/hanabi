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
    segments = state_string.split('|')
    state = {
        "fuse_tokens": int(segments[0]),
        "hint_tokens": int(segments[1]),
        "discard_pile": segments[2],
        "played_cards": segments[3]
    }
    return state

agent = HanabiAgent()
state_string = "1|7|G4R3Y2||1201031221312213211122211120103122131221321112221112010312213122132111222111201031221312213211122211|2000020000300003000020000010100222101201021210222101010022210120102121022210101002221012010211102221|2112021221312013221122211211202122131201322112221121120212213120132211222112102021221311013221122211|1011120221302013011130211101112022130201301113021110111202213020130111302111111121221311013111132211|B1R2Y4Y4|G3R4R1G2|R3R5W1B3"
encoded_state = encode_state(state_string)
print(encoded_state)