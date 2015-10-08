using UnityEngine;
using System.Collections;

public class Raptor_Movement : MonoBehaviour {

    //protected Animator _animator;
    public static bool _rotaCindyDerecha = false;
    public static bool _rotaCindyIzquierda = false;
    public static bool _cindySalta = false;
    public static bool _cindyMuere = false;
    public static bool _cindyAvanza = false;
    private int frames;
    //public static bool _cindyRegresa = false;
    public Animation kuz;
    // Use this for initialization
    void Start ()
    {
        _rotaCindyDerecha = _rotaCindyIzquierda = _cindyMuere = _cindySalta = false;
        //_animator = GetComponent<Animator>();
        //for (int i = 0; i < 16; i++)
        kuz = this.GetComponent<Animation>();
        frames = 0;
    }
	
	// Update is called once per frame
	void Update ()
    {
        if (!_cindyMuere)
        {
            if (_rotaCindyDerecha)
            {
                if (frames == 0)
                {
                    kuz.Stop();
                    kuz.Play("Look_right");
                }
                frames++;
                if (frames > 40)
                    frames = 0;
                //kuz.Stop();
                //kuz.Play("idle");
            }
            else if (_rotaCindyIzquierda)
            {
                if (frames == 0)
                {
                    kuz.Stop();
                    kuz.Play("Look_left");
                }
                frames++;
                if (frames > 40)
                    frames = 0;
                //kuz.Play("idle");
            }
            else if (_cindySalta)
            {
                if (frames == 0)
                {
                    kuz.Stop();
                    kuz.Play("Full_Jump");
                }
                frames++;
                if (frames > 40)
                    frames = 0;
                //kuz.Stop();
                //kuz.Play("idle");
            }
            else if (_cindyAvanza)
            {
                if (frames == 0)
                {
                    kuz.Stop();
                    kuz.PlayQueued("Run");
                }
                frames++;
                if (frames > 40)
                    frames = 0;
                //kuz.Stop();
                //kuz.Play("idle");
            }
            else
            {
                if (frames == 0)
                {
                    kuz.Stop();
                    kuz.Play("idle");
                }
                frames++;
                if (frames > 40)
                    frames = 0;

            }
        }
        else
        {
            //kuz.Stop();
            kuz.Play("Death");
        }
        
    }

}
