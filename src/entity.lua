local entity = {}

entity.props = {
    x = 0.0,
    y = 0.0,
    velocity = 100.0
}

a = 1

function entity:init()
    print("init");
    self.props.x = 150.0;
    self.props.y = 150.0;
end

function entity:process(delta)
    str = "I run once per every iteration of the game loop. delta: %dms";
    print(string.format(str, delta));
    self.props.x = self.props.x + self.props.velocity * delta / 1000;
end

return entity