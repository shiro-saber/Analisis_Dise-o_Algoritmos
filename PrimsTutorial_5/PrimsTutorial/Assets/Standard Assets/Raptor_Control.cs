using UnityEngine;
using System.Collections;

public class Raptor_Control : MonoBehaviour {
    protected Animator _animator;
    public static bool _rotaCindyDerecha = false;
    public static bool _rotaCindyIzquierda = false;
    public static bool _cindySalta = false;
    public static bool _cindyMuere = false;
    public static bool _cindyAvanza = false;
    // Use this for initialization
    void Start()
    {
        _rotaCindyDerecha = _rotaCindyIzquierda = _cindyMuere = _cindySalta = false;
        //_animator = GetComponent<Animator>();
        //for (int i = 0; i < 16; i++)
        _animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!_cindyMuere)
        {
            if (_rotaCindyDerecha)
            {
                _animator.SetBool("Look_right", true);
                _animator.SetBool("Look_Left", false);
                _animator.SetBool("Run", false);
                _animator.SetBool("Full_Jump", false);
            }
            else if (_rotaCindyIzquierda)
            {
                _animator.SetBool("Look_right", false);
                _animator.SetBool("Look_Left", true);
                _animator.SetBool("Run", false);
                _animator.SetBool("Full_Jump", false);
            }
            else if (_cindySalta)
            {
                _animator.SetBool("Look_right", false);
                _animator.SetBool("Look_Left", false);
                _animator.SetBool("Run", false);
                _animator.SetBool("Full_Jump", true);
            }
            else if (_cindyAvanza)
            {
                _animator.SetBool("Look_right", false);
                _animator.SetBool("Look_Left", false);
                _animator.SetBool("Run", true);
                _animator.SetBool("Full_Jump", false);
            }
            else
            {
                _animator.SetBool("Look_right", false);
                _animator.SetBool("Look_Left", false);
                _animator.SetBool("Run", false);
                _animator.SetBool("Full_Jump", false);
            }
        }
        else
        {
            _animator.SetBool("Look_right", false);
            _animator.SetBool("Look_Left", false);
            _animator.SetBool("Run", false);
            _animator.SetBool("Full_Jump", false);
            _animator.SetBool("Death", true);
        }

    }
}
