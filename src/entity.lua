local entity = {}

entity.props = {
    x = 0.0,
    y = 0.0,
    velocity = 100.0
}

function entity:init()
    --print("init");
    self.props.x = 150.0;
    self.props.y = 150.0;
end

function entity:process(delta)
    --str = "I run once per every iteration of the game loop. delta: %f ms";
    --print(string.format(str, delta * 1000));
    self.props.x = self.props.x + self.props.velocity * delta;
end

return entity