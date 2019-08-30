#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
const float offset = 1.0 / 300.0;
void main()
{
	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    FragColor = vec4(col, 1.0);
} 



public class Move : MonoBehaviour 
{
    private GameObject ball;
    public speed = 5.0f;
    bool left = true;//方向
    void OnStart()
    {
        ball = GameObject.CreatePrimitive(PrimitiveType.Sphere);//创建个球球
        ball.transform = new Vec3(10.0f, 0.0f, 0.0f);
    }

    void Update() {
        if (ball.transform.x < -10.0f)
        {
            left = false;
        }
        if (ball.transform.x > 10.0f)
        {
            left = true;
        }
        ball.transform += new Vec3(speed * Time.deltaTime * left ? -1 : 1 , 0.0f, 0.0f);//根据方向移动
    }
}


public class Move : MonoBehaviour 
{
    private GameObject ball;
    public speed = 5.0f;
    bool left = true;//方向
    void OnStart()
    {
        ball = GameObject.CreatePrimitive(PrimitiveType.Sphere);//创建个球球
        ball.transform = new Vec3(10.0f, 0.0f, 0.0f);
    }

    void Update() {
        if (ball.transform.x < -10.0f)
        {
            left = false;
        }
        if (ball.transform.x > 10.0f)
        {
            left = true;
        }
        ball.transform.position += new Vec3(speed * Time.deltaTime * left ? -1 : 1 , 0.0f, 0.0f);//根据方向移动
    }
}


public class ExampleClass : MonoBehaviour
{
    void OnStart()
    {

    }
    void Update()
    {
        if (Input.GetKeyDown("space"))
        {
            Vector3 position = new Vector3(Random.Range(-10.0f, 10.0f), Random.Range(-10.0f, 10.0f), Random.Range(-10.0f, 10.0f));
            GameObject go = GameObject.CreatePrimitive(PrimitiveType.Cube);//创建个方方
            go.transform.position = position;
        }
    }
}


public class ExampleClass : MonoBehaviour
{
    void OnStart()
    {
         GameObject go = GameObject.CreatePrimitive(PrimitiveType.Sphere);//创建个球球
         go.AddComponent(typeof(SphereCollider));
    }
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            //创建一条从摄像机到触摸位置的射线
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition); // 定义射线
            RaycastHit rayHit;
            if (Physics.Raycast(ray, out rayHit, layerGround))  // 参数1 射线，参数2 碰撞信息， 参数3 碰撞层
            {
                //打印射线碰撞到的对象需要挂载Collider盒子
                print("info   " + rayHit.collider.gameObject.name);
            }
        }
    }
}